#ifndef JSON_H
#define JSON_H
#include <istream>
#include <ostream>
#include <sstream>
#include <typeindex>
#include <type_traits>
#include <functional>
#include "Reflect.h"

namespace Json
{
    using namespace ExtendedTypeSupport;
    using namespace Reflect;
    
    inline namespace Annotations
    {
        /// Field annotation telling JSON to explicitly use the numeric value of an enum
        struct EnumInt {};

        struct Unspecialized {};

        template <typename T>
        struct is_specialized
        {
            static constexpr bool value = !std::is_base_of<Unspecialized, T>::value;
        };

        struct IsRoot {};
    }
    
    inline namespace Shared
    {
        enum class Statics
        {
            Excluded = 0,
            Included = 1,
            Only = 2
        };

        template <bool IsStatic, Statics statics>
        struct matches_statics
        {
            constexpr static bool value =
                statics == Statics::Included ||
                statics == Statics::Excluded && !IsStatic ||
                statics == Statics::Only && IsStatic;
        };

        template <Statics statics, typename Object>
        static constexpr size_t FirstIndex()
        {
            if constexpr ( statics == Statics::Only || statics == Statics::Excluded )
            {
                for ( size_t i=0; i<Object::Class::TotalFields; i++ )
                {
                    if constexpr ( statics == Statics::Only && Object::Class::Fields[i].IsStatic )
                        return i;
                    else if constexpr ( statics == Statics::Excluded && !Object::Class::Fields[i].IsStatic )
                        return i;
                }
            }
            return 0;
        }

        constexpr size_t NoFieldIndex = std::numeric_limits<size_t>::max();
        using NoField = Fields::Field<>;

        template <typename T>
        using ReflectedField = Fields::Field<T, void*, 0, IsRoot>;

        struct Context
        {
            virtual ~Context() {}
        };
        Context context;

        class Exception : public std::exception
        {
        public:
            Exception(const char* what) : std::exception(what) {}
        };

        inline namespace TypeNames
        {
            std::string simplifyTypeStr(const std::string & superTypeStr)
            {
                std::string rawSimpleTypeStr = superTypeStr;
                if ( rawSimpleTypeStr.find("struct ", 0) != std::string::npos )
                    rawSimpleTypeStr.erase(0, strlen("struct "));
                if ( rawSimpleTypeStr.find("class ", 0) != std::string::npos )
                    rawSimpleTypeStr.erase(0, strlen("class "));

                std::string simpleTypeStr;
                for ( size_t i=0; i<rawSimpleTypeStr.size(); i++ )
                {
                    if ( rawSimpleTypeStr[i] != ' ' )
                        simpleTypeStr += rawSimpleTypeStr[i];
                    else if ( ++i < rawSimpleTypeStr.size() ) // Remove space and upper-case the letter following the space
                        simpleTypeStr += std::toupper(rawSimpleTypeStr[i]);
                }

                return simpleTypeStr;
            }

            template <typename T>
            std::string superTypeToJsonFieldName()
            {
                return std::string("__") + simplifyTypeStr(TypeToStr<T>());
            }
        }
    };

    inline namespace Generic
    {
        class JsonField
        {
        public:
            enum_t(Type, size_t, {
                Regular = 0,
                SuperClass = 1
            });
        
            JsonField() : index(0), type(Type::Regular), name("") {}
            JsonField(size_t index, Type fieldType, const std::string & name) : index(index), type(fieldType), name(name) {}
        
            size_t index;
            Type type;
            std::string name;
        };

        class Value;
        using ObjectPtr = std::shared_ptr<std::map<std::string, std::shared_ptr<Value>>>;
        using FieldsPtr = std::shared_ptr<std::map<std::string, std::shared_ptr<Value>>>;

        class Value {
        public:
            enum_t(Type, uint8_t, {
                None,
                Boolean,
                Number,
                String,
                Object,
                Array,
                BoolArray,
                NumberArray,
                StringArray,
                ObjectArray,
                MixedArray
            });

            virtual ~Value() {};

            virtual Type type() const = 0;
            
            virtual bool & boolean() = 0;
            virtual std::string & number() = 0;
            virtual std::string & string() = 0;
            virtual std::map<std::string, std::shared_ptr<Value>> & object() = 0;

            virtual const bool & boolean() const = 0;
            virtual const std::string & number() const = 0;
            virtual const std::string & string() const = 0;
            virtual const std::map<std::string, std::shared_ptr<Value>> & object() const = 0;

            virtual size_t arraySize() const = 0;

            virtual std::vector<bool> & boolArray() = 0;
            virtual std::vector<std::string> & numberArray() = 0;
            virtual std::vector<std::string> & stringArray() = 0;
	        virtual std::vector<std::map<std::string, std::shared_ptr<Value>>> & objectArray() = 0;
	        virtual std::vector<std::shared_ptr<Value>> & mixedArray() = 0;
            
            virtual const std::vector<bool> & boolArray() const = 0;
            virtual const std::vector<std::string> & numberArray() const = 0;
            virtual const std::vector<std::string> & stringArray() const = 0;
	        virtual const std::vector<std::map<std::string, std::shared_ptr<Value>>> & objectArray() const = 0;
	        virtual const std::vector<std::shared_ptr<Value>> & mixedArray() const = 0;

            template <typename T>
            bool getNumber(T & num) const
            {
                return (std::stringstream(number()) >> num).good();
            }

            template <typename T>
            void setNumber(const T & number)
            {
                number() = std::to_string(number);
            }

        };
	    
        class TypeMismatch : public Exception
        {
        public:
            static std::string getTypeStr(Value::Type type)
            {
                switch ( type )
                {
                    case Value::Type::None: return "None";
                    case Value::Type::Boolean: return "Boolean";
                    case Value::Type::Number: return "Number";
                    case Value::Type::String: return "String";
                    case Value::Type::Object: return "Object";
                    case Value::Type::Array: return "Array";
                    case Value::Type::BoolArray: return "BoolArray";
                    case Value::Type::NumberArray: return "NumberArray";
                    case Value::Type::StringArray: return "StringArray";
                    case Value::Type::ObjectArray: return "ObjectArray";
                    case Value::Type::MixedArray: return "MixedArray";
                }
                return "Unknown";
            }

            TypeMismatch(Value::Type valueType, Value::Type functionType, const std::string & functionName)
                : Exception((std::string("Cannot call ") + functionName + "() on a Json::" + getTypeStr(valueType) + " type!").c_str()),
                valueType(valueType), functionType(functionType) {}

            Value::Type valueType;
            Value::Type functionType;
        };

        class Bool : public Value {
        public:
            Bool() : value(false) {}
            Bool(bool value) : value(value) {}
            Bool(const Bool & other) : value(other.value) {}
            virtual ~Bool() {}
            
            static std::shared_ptr<Value> Make() { return std::shared_ptr<Value>(new Bool()); }
            static std::shared_ptr<Value> Make(bool value) { return std::shared_ptr<Value>(new Bool(value)); }
            static std::shared_ptr<Value> Make(const Bool & other) { return std::shared_ptr<Value>(new Bool(other)); }
            
            virtual Type type() const { return Value::Type::Boolean; }
            
            virtual bool & boolean() { return value; }
            virtual std::string & number() { throw TypeMismatch(Value::Type::Boolean, Value::Type::Number, "number"); }
            virtual std::string & string() { throw TypeMismatch(Value::Type::Boolean, Value::Type::String, "string"); }
            virtual std::map<std::string, std::shared_ptr<Value>> & object() { throw TypeMismatch(Value::Type::Boolean, Value::Type::Object, "object"); }

            virtual const bool & boolean() const { return value; }
            virtual const std::string & number() const { throw TypeMismatch(Value::Type::Boolean, Value::Type::Number, "number"); }
            virtual const std::string & string() const { throw TypeMismatch(Value::Type::Boolean, Value::Type::String, "string"); }
            virtual const std::map<std::string, std::shared_ptr<Value>> & object() const { throw TypeMismatch(Value::Type::Boolean, Value::Type::Object, "object"); }

            virtual size_t arraySize() const { throw TypeMismatch(Value::Type::Boolean, Value::Type::Array, "arraySize"); }

            virtual std::vector<bool> & boolArray() { throw TypeMismatch(Value::Type::Boolean, Value::Type::BoolArray, "boolArray"); }
            virtual std::vector<std::string> & numberArray() { throw TypeMismatch(Value::Type::Boolean, Value::Type::NumberArray, "numberArray"); }
            virtual std::vector<std::string> & stringArray() { throw TypeMismatch(Value::Type::Boolean, Value::Type::StringArray, "stringArray"); }
	        virtual std::vector<std::map<std::string, std::shared_ptr<Value>>> & objectArray() {
                throw TypeMismatch(Value::Type::Boolean, Value::Type::ObjectArray, "objectArray");
            }
            virtual std::vector<std::shared_ptr<Value>> & mixedArray() { throw TypeMismatch(Value::Type::Boolean, Value::Type::MixedArray, "mixedArray"); }

            virtual const std::vector<bool> & boolArray() const { throw TypeMismatch(Value::Type::Boolean, Value::Type::BoolArray, "boolArray"); }
            virtual const std::vector<std::string> & numberArray() const { throw TypeMismatch(Value::Type::Boolean, Value::Type::NumberArray, "numberArray"); }
            virtual const std::vector<std::string> & stringArray() const { throw TypeMismatch(Value::Type::Boolean, Value::Type::StringArray, "stringArray"); }
	        virtual const std::vector<std::map<std::string, std::shared_ptr<Value>>> & objectArray() const {
                throw TypeMismatch(Value::Type::Boolean, Value::Type::ObjectArray, "objectArray");
            }
            virtual const std::vector<std::shared_ptr<Value>> & mixedArray() const { throw TypeMismatch(Value::Type::Boolean, Value::Type::MixedArray, "mixedArray"); }

        private:
	        bool value;
        };
        class Number : public Value {
        public:
            Number() : value() {}
            Number(const std::string & value) : value(value) {}
            Number(const Number & other) : value(other.value) {}
            virtual ~Number() {}
            
            static std::shared_ptr<Value> Make() { return std::shared_ptr<Value>(new Number()); }
            static std::shared_ptr<Value> Make(const std::string & value) { return std::shared_ptr<Value>(new Number(value)); }
            static std::shared_ptr<Value> Make(const Number & other) { return std::shared_ptr<Value>(new Number(other)); }
            template <typename T> static std::shared_ptr<Value> Make(const T & number) { return std::shared_ptr<Value>(new Number(std::to_string(number))); }
            
            virtual Type type() const { return Value::Type::Number; }
            
            virtual bool & boolean() { throw TypeMismatch(Value::Type::Number, Value::Type::Boolean, "bool"); }
            virtual std::string & number() { return value; }
            virtual std::string & string() { throw TypeMismatch(Value::Type::Number, Value::Type::String, "string"); }
            virtual std::map<std::string, std::shared_ptr<Value>> & object() { throw TypeMismatch(Value::Type::Number, Value::Type::Object, "object"); }

            virtual const bool & boolean() const { throw TypeMismatch(Value::Type::Number, Value::Type::Boolean, "bool"); }
            virtual const std::string & number() const { return value; }
            virtual const std::string & string() const { throw TypeMismatch(Value::Type::Number, Value::Type::String, "string"); }
            virtual const std::map<std::string, std::shared_ptr<Value>> & object() const { throw TypeMismatch(Value::Type::Number, Value::Type::Object, "object"); }

            virtual size_t arraySize() const { throw TypeMismatch(Value::Type::Number, Value::Type::Array, "arraySize"); }

            virtual std::vector<bool> & boolArray() { throw TypeMismatch(Value::Type::Number, Value::Type::BoolArray, "boolArray"); }
            virtual std::vector<std::string> & numberArray() { throw TypeMismatch(Value::Type::Number, Value::Type::NumberArray, "numberArray"); }
            virtual std::vector<std::string> & stringArray() { throw TypeMismatch(Value::Type::Number, Value::Type::StringArray, "stringArray"); }
	        virtual std::vector<std::map<std::string, std::shared_ptr<Value>>> & objectArray() {
                throw TypeMismatch(Value::Type::Number, Value::Type::ObjectArray, "objectArray");
            }
            virtual std::vector<std::shared_ptr<Value>> & mixedArray() { throw TypeMismatch(Value::Type::Number, Value::Type::MixedArray, "mixedArray"); }

            virtual const std::vector<bool> & boolArray() const { throw TypeMismatch(Value::Type::Number, Value::Type::BoolArray, "boolArray"); }
            virtual const std::vector<std::string> & numberArray() const { throw TypeMismatch(Value::Type::Number, Value::Type::NumberArray, "numberArray"); }
            virtual const std::vector<std::string> & stringArray() const { throw TypeMismatch(Value::Type::Number, Value::Type::StringArray, "stringArray"); }
	        virtual const std::vector<std::map<std::string, std::shared_ptr<Value>>> & objectArray() const {
                throw TypeMismatch(Value::Type::Number, Value::Type::ObjectArray, "objectArray");
            }
            virtual const std::vector<std::shared_ptr<Value>> & mixedArray() const { throw TypeMismatch(Value::Type::Number, Value::Type::MixedArray, "mixedArray"); }
            
        private:
	        std::string value;
        };
        class String : public Value {
        public:
            String() : value() {}
            String(const std::string & value) : value(value) {}
            String(const String & other) : value(other.value) {}
            virtual ~String() {}
            
            static std::shared_ptr<Value> Make() { return std::shared_ptr<Value>(new String()); }
            static std::shared_ptr<Value> Make(const std::string & value) { return std::shared_ptr<Value>(new String(value)); }
            static std::shared_ptr<Value> Make(const String & other) { return std::shared_ptr<Value>(new String(other)); }
            
            virtual Type type() const { return Value::Type::String; }
            
            virtual bool & boolean() { throw TypeMismatch(Value::Type::String, Value::Type::Boolean, "bool"); }
            virtual std::string & number() { throw TypeMismatch(Value::Type::String, Value::Type::Number, "number"); }
            virtual std::string & string() { return value; }
            virtual std::map<std::string, std::shared_ptr<Value>> & object() { throw TypeMismatch(Value::Type::String, Value::Type::Object, "object"); }

            virtual const bool & boolean() const { throw TypeMismatch(Value::Type::String, Value::Type::Boolean, "bool"); }
            virtual const std::string & number() const { throw TypeMismatch(Value::Type::String, Value::Type::Number, "number"); }
            virtual const std::string & string() const { return value; }
            virtual const std::map<std::string, std::shared_ptr<Value>> & object() const { throw TypeMismatch(Value::Type::String, Value::Type::Object, "object"); }

            virtual size_t arraySize() const { throw TypeMismatch(Value::Type::String, Value::Type::Array, "arraySize"); }

            virtual std::vector<bool> & boolArray() { throw TypeMismatch(Value::Type::String, Value::Type::BoolArray, "boolArray"); }
            virtual std::vector<std::string> & numberArray() { throw TypeMismatch(Value::Type::String, Value::Type::NumberArray, "numberArray"); }
            virtual std::vector<std::string> & stringArray() { throw TypeMismatch(Value::Type::String, Value::Type::StringArray, "stringArray"); }
	        virtual std::vector<std::map<std::string, std::shared_ptr<Value>>> & objectArray() {
                throw TypeMismatch(Value::Type::String, Value::Type::ObjectArray, "objectArray");
            }
            virtual std::vector<std::shared_ptr<Value>> & mixedArray() { throw TypeMismatch(Value::Type::String, Value::Type::MixedArray, "mixedArray"); }

            virtual const std::vector<bool> & boolArray() const { throw TypeMismatch(Value::Type::String, Value::Type::BoolArray, "boolArray"); }
            virtual const std::vector<std::string> & numberArray() const { throw TypeMismatch(Value::Type::String, Value::Type::NumberArray, "numberArray"); }
            virtual const std::vector<std::string> & stringArray() const { throw TypeMismatch(Value::Type::String, Value::Type::StringArray, "stringArray"); }
	        virtual const std::vector<std::map<std::string, std::shared_ptr<Value>>> & objectArray() const {
                throw TypeMismatch(Value::Type::String, Value::Type::ObjectArray, "objectArray");
            }
            virtual const std::vector<std::shared_ptr<Value>> & mixedArray() const { throw TypeMismatch(Value::Type::String, Value::Type::MixedArray, "mixedArray"); }
            
        private:
	        std::string value;
        };
        class Object : public Value {
        public:
            Object() : value() {}
            Object(const Object & other) : value(other.value) {}
            virtual ~Object() {}
            
            static std::shared_ptr<Value> Make() { return std::shared_ptr<Value>(new Object()); }
            static std::shared_ptr<Value> Make(const Object & other) { return std::shared_ptr<Value>(new Object(other)); }
            
            virtual Type type() const { return Value::Type::Object; }
            
            virtual bool & boolean() { throw TypeMismatch(Value::Type::Object, Value::Type::Boolean, "bool"); }
            virtual std::string & number() { throw TypeMismatch(Value::Type::Object, Value::Type::Number, "number"); }
            virtual std::string & string() { throw TypeMismatch(Value::Type::Object, Value::Type::String, "string"); }
            virtual std::map<std::string, std::shared_ptr<Value>> & object() { return value; }
            
            virtual const bool & boolean() const { throw TypeMismatch(Value::Type::Object, Value::Type::Boolean, "bool"); }
            virtual const std::string & number() const { throw TypeMismatch(Value::Type::Object, Value::Type::Number, "number"); }
            virtual const std::string & string() const { throw TypeMismatch(Value::Type::Object, Value::Type::String, "string"); }
            virtual const std::map<std::string, std::shared_ptr<Value>> & object() const { return value; }

            virtual size_t arraySize() const { throw TypeMismatch(Value::Type::Object, Value::Type::Array, "arraySize"); }

            virtual std::vector<bool> & boolArray() { throw TypeMismatch(Value::Type::Object, Value::Type::BoolArray, "boolArray"); }
            virtual std::vector<std::string> & numberArray() { throw TypeMismatch(Value::Type::Object, Value::Type::NumberArray, "numberArray"); }
            virtual std::vector<std::string> & stringArray() { throw TypeMismatch(Value::Type::Object, Value::Type::StringArray, "stringArray"); }
	        virtual std::vector<std::map<std::string, std::shared_ptr<Value>>> & objectArray() {
                throw TypeMismatch(Value::Type::Object, Value::Type::ObjectArray, "objectArray");
            }
            virtual std::vector<std::shared_ptr<Value>> & mixedArray() { throw TypeMismatch(Value::Type::Object, Value::Type::MixedArray, "mixedArray"); }

            virtual const std::vector<bool> & boolArray() const { throw TypeMismatch(Value::Type::Object, Value::Type::BoolArray, "boolArray"); }
            virtual const std::vector<std::string> & numberArray() const { throw TypeMismatch(Value::Type::Object, Value::Type::NumberArray, "numberArray"); }
            virtual const std::vector<std::string> & stringArray() const { throw TypeMismatch(Value::Type::Object, Value::Type::StringArray, "stringArray"); }
	        virtual const std::vector<std::map<std::string, std::shared_ptr<Value>>> & objectArray() const {
                throw TypeMismatch(Value::Type::Object, Value::Type::ObjectArray, "objectArray");
            }
            virtual const std::vector<std::shared_ptr<Value>> & mixedArray() const { throw TypeMismatch(Value::Type::Object, Value::Type::MixedArray, "mixedArray"); }
            
            virtual void put(std::string fieldName, std::shared_ptr<Value> value)
            {
                this->value.insert(std::pair<std::string, std::shared_ptr<Value>>(fieldName, value));
            }
            
        private:
	        std::map<std::string, std::shared_ptr<Value>> value;
        };
	
        class BoolArray : public Value {
        public:
            BoolArray() : values() {}
            BoolArray(const BoolArray & other) : values(other.values) {}
            virtual ~BoolArray() {}
            
            static std::shared_ptr<Value> Make() { return std::shared_ptr<Value>(new BoolArray()); }
            static std::shared_ptr<Value> Make(const BoolArray & other) { return std::shared_ptr<Value>(new BoolArray(other)); }

            virtual Type type() const { return Value::Type::BoolArray; }
            
            virtual bool & boolean() { throw TypeMismatch(Value::Type::BoolArray, Value::Type::Boolean, "bool"); }
            virtual std::string & number() { throw TypeMismatch(Value::Type::BoolArray, Value::Type::Number, "number"); }
            virtual std::string & string() { throw TypeMismatch(Value::Type::BoolArray, Value::Type::String, "string"); }
            virtual std::map<std::string, std::shared_ptr<Value>> & object() { throw TypeMismatch(Value::Type::BoolArray, Value::Type::Object, "object"); }
            
            virtual const bool & boolean() const { throw TypeMismatch(Value::Type::BoolArray, Value::Type::Boolean, "bool"); }
            virtual const std::string & number() const { throw TypeMismatch(Value::Type::BoolArray, Value::Type::Number, "number"); }
            virtual const std::string & string() const { throw TypeMismatch(Value::Type::BoolArray, Value::Type::String, "string"); }
            virtual const std::map<std::string, std::shared_ptr<Value>> & object() const { throw TypeMismatch(Value::Type::BoolArray, Value::Type::Object, "object"); }

            virtual size_t arraySize() const { throw TypeMismatch(Value::Type::BoolArray, Value::Type::Array, "arraySize"); }
            
            virtual std::vector<bool> & boolArray() { return values; }
            virtual std::vector<std::string> & numberArray() { throw TypeMismatch(Value::Type::BoolArray, Value::Type::NumberArray, "numberArray"); }
            virtual std::vector<std::string> & stringArray() { throw TypeMismatch(Value::Type::BoolArray, Value::Type::StringArray, "stringArray"); }
	        virtual std::vector<std::map<std::string, std::shared_ptr<Value>>> & objectArray() {
                throw TypeMismatch(Value::Type::BoolArray, Value::Type::ObjectArray, "objectArray");
            }
            virtual std::vector<std::shared_ptr<Value>> & mixedArray() { throw TypeMismatch(Value::Type::BoolArray, Value::Type::MixedArray, "mixedArray"); }
            
            virtual const std::vector<bool> & boolArray() const { return values; }
            virtual const std::vector<std::string> & numberArray() const { throw TypeMismatch(Value::Type::BoolArray, Value::Type::NumberArray, "numberArray"); }
            virtual const std::vector<std::string> & stringArray() const { throw TypeMismatch(Value::Type::BoolArray, Value::Type::StringArray, "stringArray"); }
	        virtual const std::vector<std::map<std::string, std::shared_ptr<Value>>> & objectArray() const {
                throw TypeMismatch(Value::Type::BoolArray, Value::Type::ObjectArray, "objectArray");
            }
            virtual const std::vector<std::shared_ptr<Value>> & mixedArray() const { throw TypeMismatch(Value::Type::BoolArray, Value::Type::MixedArray, "mixedArray"); }
            
        private:
	        std::vector<bool> values;
        };
        class NumberArray : public Value {
        public:
            NumberArray() : values() {}
            NumberArray(const NumberArray & other) : values(other.values) {}
            virtual ~NumberArray() {}
            
            static std::shared_ptr<Value> Make() { return std::shared_ptr<Value>(new NumberArray()); }
            static std::shared_ptr<Value> Make(const NumberArray & other) { return std::shared_ptr<Value>(new NumberArray(other)); }
            
            virtual Type type() const { return Value::Type::NumberArray; }
            
            virtual bool & boolean() { throw TypeMismatch(Value::Type::NumberArray, Value::Type::Boolean, "bool"); }
            virtual std::string & number() { throw TypeMismatch(Value::Type::NumberArray, Value::Type::Number, "number"); }
            virtual std::string & string() { throw TypeMismatch(Value::Type::NumberArray, Value::Type::String, "string"); }
            virtual std::map<std::string, std::shared_ptr<Value>> & object() { throw TypeMismatch(Value::Type::NumberArray, Value::Type::Object, "object"); }
            
            virtual const bool & boolean() const { throw TypeMismatch(Value::Type::NumberArray, Value::Type::Boolean, "bool"); }
            virtual const std::string & number() const { throw TypeMismatch(Value::Type::NumberArray, Value::Type::Number, "number"); }
            virtual const std::string & string() const { throw TypeMismatch(Value::Type::NumberArray, Value::Type::String, "string"); }
            virtual const std::map<std::string, std::shared_ptr<Value>> & object() const { throw TypeMismatch(Value::Type::NumberArray, Value::Type::Object, "object"); }

            virtual size_t arraySize() const { throw TypeMismatch(Value::Type::NumberArray, Value::Type::Array, "arraySize"); }

            virtual std::vector<bool> & boolArray() { throw TypeMismatch(Value::Type::NumberArray, Value::Type::BoolArray, "boolArray"); }
            virtual std::vector<std::string> & numberArray() { return values; }
            virtual std::vector<std::string> & stringArray() { throw TypeMismatch(Value::Type::NumberArray, Value::Type::StringArray, "stringArray"); }
	        virtual std::vector<std::map<std::string, std::shared_ptr<Value>>> & objectArray() {
                throw TypeMismatch(Value::Type::NumberArray, Value::Type::ObjectArray, "objectArray");
            }
            virtual std::vector<std::shared_ptr<Value>> & mixedArray() { throw TypeMismatch(Value::Type::NumberArray, Value::Type::MixedArray, "mixedArray"); }

            virtual const std::vector<bool> & boolArray() const { throw TypeMismatch(Value::Type::NumberArray, Value::Type::BoolArray, "boolArray"); }
            virtual const std::vector<std::string> & numberArray() const { return values; }
            virtual const std::vector<std::string> & stringArray() const { throw TypeMismatch(Value::Type::NumberArray, Value::Type::StringArray, "stringArray"); }
	        virtual const std::vector<std::map<std::string, std::shared_ptr<Value>>> & objectArray() const {
                throw TypeMismatch(Value::Type::NumberArray, Value::Type::ObjectArray, "objectArray");
            }
            virtual const std::vector<std::shared_ptr<Value>> & mixedArray() const { throw TypeMismatch(Value::Type::NumberArray, Value::Type::MixedArray, "mixedArray"); }
            
        private:
	        std::vector<std::string> values;
        };
        class StringArray : public Value {
        public:
            StringArray() : values() {}
            StringArray(const StringArray & other) : values(other.values) {}
            virtual ~StringArray() {}
            
            static std::shared_ptr<Value> Make() { return std::shared_ptr<Value>(new StringArray()); }
            static std::shared_ptr<Value> Make(const StringArray & other) { return std::shared_ptr<Value>(new StringArray(other)); }
            
            virtual Type type() const { return Value::Type::StringArray; }
            
            virtual bool & boolean() { throw TypeMismatch(Value::Type::StringArray, Value::Type::Boolean, "bool"); }
            virtual std::string & number() { throw TypeMismatch(Value::Type::StringArray, Value::Type::Number, "number"); }
            virtual std::string & string() { throw TypeMismatch(Value::Type::StringArray, Value::Type::String, "string"); }
            virtual std::map<std::string, std::shared_ptr<Value>> & object() { throw TypeMismatch(Value::Type::StringArray, Value::Type::Object, "object"); }
            
            virtual const bool & boolean() const { throw TypeMismatch(Value::Type::StringArray, Value::Type::Boolean, "bool"); }
            virtual const std::string & number() const { throw TypeMismatch(Value::Type::StringArray, Value::Type::Number, "number"); }
            virtual const std::string & string() const { throw TypeMismatch(Value::Type::StringArray, Value::Type::String, "string"); }
            virtual const std::map<std::string, std::shared_ptr<Value>> & object() const { throw TypeMismatch(Value::Type::StringArray, Value::Type::Object, "object"); }

            virtual size_t arraySize() const { throw TypeMismatch(Value::Type::StringArray, Value::Type::Array, "arraySize"); }

            virtual std::vector<bool> & boolArray() { throw TypeMismatch(Value::Type::StringArray, Value::Type::BoolArray, "boolArray"); }
            virtual std::vector<std::string> & numberArray() { throw TypeMismatch(Value::Type::StringArray, Value::Type::NumberArray, "numberArray"); }
            virtual std::vector<std::string> & stringArray() { return values; }
	        virtual std::vector<std::map<std::string, std::shared_ptr<Value>>> & objectArray() {
                throw TypeMismatch(Value::Type::StringArray, Value::Type::ObjectArray, "objectArray");
            }
            virtual std::vector<std::shared_ptr<Value>> & mixedArray() { throw TypeMismatch(Value::Type::StringArray, Value::Type::MixedArray, "mixedArray"); }

            virtual const std::vector<bool> & boolArray() const { throw TypeMismatch(Value::Type::StringArray, Value::Type::BoolArray, "boolArray"); }
            virtual const std::vector<std::string> & numberArray() const { throw TypeMismatch(Value::Type::StringArray, Value::Type::NumberArray, "numberArray"); }
            virtual const std::vector<std::string> & stringArray() const { return values; }
	        virtual const std::vector<std::map<std::string, std::shared_ptr<Value>>> & objectArray() const {
                throw TypeMismatch(Value::Type::StringArray, Value::Type::ObjectArray, "objectArray");
            }
            virtual const std::vector<std::shared_ptr<Value>> & mixedArray() const { throw TypeMismatch(Value::Type::StringArray, Value::Type::MixedArray, "mixedArray"); }

        private:
	        std::vector<std::string> values;
        };
        class ObjectArray : public Value {
        public:
            ObjectArray() : values() {}
            ObjectArray(const ObjectArray & other) : values(other.values) {}
            virtual ~ObjectArray() {}
            
            static std::shared_ptr<Value> Make() { return std::shared_ptr<Value>(new ObjectArray()); }
            static std::shared_ptr<Value> Make(const ObjectArray & other) { return std::shared_ptr<Value>(new ObjectArray(other)); }
            
            virtual Type type() const { return Value::Type::ObjectArray; }
            
            virtual bool & boolean() { throw TypeMismatch(Value::Type::ObjectArray, Value::Type::Boolean, "bool"); }
            virtual std::string & number() { throw TypeMismatch(Value::Type::ObjectArray, Value::Type::Number, "number"); }
            virtual std::string & string() { throw TypeMismatch(Value::Type::ObjectArray, Value::Type::String, "string"); }
            virtual std::map<std::string, std::shared_ptr<Value>> & object() { throw TypeMismatch(Value::Type::ObjectArray, Value::Type::Object, "object"); }
            
            virtual const bool & boolean() const { throw TypeMismatch(Value::Type::ObjectArray, Value::Type::Boolean, "bool"); }
            virtual const std::string & number() const { throw TypeMismatch(Value::Type::ObjectArray, Value::Type::Number, "number"); }
            virtual const std::string & string() const { throw TypeMismatch(Value::Type::ObjectArray, Value::Type::String, "string"); }
            virtual const std::map<std::string, std::shared_ptr<Value>> & object() const { throw TypeMismatch(Value::Type::ObjectArray, Value::Type::Object, "object"); }

            virtual size_t arraySize() const { throw TypeMismatch(Value::Type::ObjectArray, Value::Type::Array, "arraySize"); }

            virtual std::vector<bool> & boolArray() { throw TypeMismatch(Value::Type::ObjectArray, Value::Type::BoolArray, "boolArray"); }
            virtual std::vector<std::string> & numberArray() { throw TypeMismatch(Value::Type::ObjectArray, Value::Type::NumberArray, "numberArray"); }
            virtual std::vector<std::string> & stringArray() { throw TypeMismatch(Value::Type::ObjectArray, Value::Type::StringArray, "stringArray"); }
            virtual std::vector<std::map<std::string, std::shared_ptr<Value>>> & objectArray() { return values; }
            virtual std::vector<std::shared_ptr<Value>> & mixedArray() { throw TypeMismatch(Value::Type::ObjectArray, Value::Type::MixedArray, "mixedArray"); }

            virtual const std::vector<bool> & boolArray() const { throw TypeMismatch(Value::Type::ObjectArray, Value::Type::BoolArray, "boolArray"); }
            virtual const std::vector<std::string> & numberArray() const { throw TypeMismatch(Value::Type::ObjectArray, Value::Type::NumberArray, "numberArray"); }
            virtual const std::vector<std::string> & stringArray() const { throw TypeMismatch(Value::Type::ObjectArray, Value::Type::StringArray, "stringArray"); }
            virtual const std::vector<std::map<std::string, std::shared_ptr<Value>>> & objectArray() const { return values; }
            virtual const std::vector<std::shared_ptr<Value>> & mixedArray() const { throw TypeMismatch(Value::Type::ObjectArray, Value::Type::MixedArray, "mixedArray"); }
            
        private:
	        std::vector<std::map<std::string, std::shared_ptr<Value>>> values;
        };
        class MixedArray : public Value {
        public:
            MixedArray() : values() {}
            MixedArray(const MixedArray & other) : values(other.values) {}
            virtual ~MixedArray() {}
            
            static std::shared_ptr<Value> Make() { return std::shared_ptr<Value>(new MixedArray()); }
            static std::shared_ptr<Value> Make(const MixedArray & other) { return std::shared_ptr<Value>(new MixedArray(other)); }
            
            virtual Type type() const { return Value::Type::MixedArray; }
            
            virtual bool & boolean() { throw TypeMismatch(Value::Type::MixedArray, Value::Type::Boolean, "bool"); }
            virtual std::string & number() { throw TypeMismatch(Value::Type::MixedArray, Value::Type::Number, "number"); }
            virtual std::string & string() { throw TypeMismatch(Value::Type::MixedArray, Value::Type::String, "string"); }
            virtual std::map<std::string, std::shared_ptr<Value>> & object() { throw TypeMismatch(Value::Type::MixedArray, Value::Type::Object, "object"); }
            
            virtual const bool & boolean() const { throw TypeMismatch(Value::Type::MixedArray, Value::Type::Boolean, "bool"); }
            virtual const std::string & number() const { throw TypeMismatch(Value::Type::MixedArray, Value::Type::Number, "number"); }
            virtual const std::string & string() const { throw TypeMismatch(Value::Type::MixedArray, Value::Type::String, "string"); }
            virtual const std::map<std::string, std::shared_ptr<Value>> & object() const { throw TypeMismatch(Value::Type::MixedArray, Value::Type::Object, "object"); }

            virtual size_t arraySize() const { throw TypeMismatch(Value::Type::MixedArray, Value::Type::Array, "arraySize"); }

            virtual std::vector<bool> & boolArray() { throw TypeMismatch(Value::Type::MixedArray, Value::Type::BoolArray, "boolArray"); }
            virtual std::vector<std::string> & numberArray() { throw TypeMismatch(Value::Type::MixedArray, Value::Type::NumberArray, "numberArray"); }
            virtual std::vector<std::string> & stringArray() { throw TypeMismatch(Value::Type::MixedArray, Value::Type::StringArray, "stringArray"); }
	        virtual std::vector<std::map<std::string, std::shared_ptr<Value>>> & objectArray() {
                throw TypeMismatch(Value::Type::MixedArray, Value::Type::ObjectArray, "objectArray");
            }
            virtual std::vector<std::shared_ptr<Value>> & mixedArray() { return values; }

            virtual const std::vector<bool> & boolArray() const { throw TypeMismatch(Value::Type::MixedArray, Value::Type::BoolArray, "boolArray"); }
            virtual const std::vector<std::string> & numberArray() const { throw TypeMismatch(Value::Type::MixedArray, Value::Type::NumberArray, "numberArray"); }
            virtual const std::vector<std::string> & stringArray() const { throw TypeMismatch(Value::Type::MixedArray, Value::Type::StringArray, "stringArray"); }
	        virtual const std::vector<std::map<std::string, std::shared_ptr<Value>>> & objectArray() const {
                throw TypeMismatch(Value::Type::MixedArray, Value::Type::ObjectArray, "objectArray");
            }
            virtual const std::vector<std::shared_ptr<Value>> & mixedArray() const { return values; }

        private:
            std::vector<std::shared_ptr<Value>> values;
        };
    };
    
    inline namespace Output
    {
        constexpr const char twoSpaces[] = "  ";
        
        inline namespace Customizers
        {
            template <typename Object, typename Value,
                size_t FieldIndex = NoFieldIndex, typename OpAnnotations = Annotate<>, typename Field = NoField, Statics statics = Statics::Excluded,
                bool PrettyPrint = false, size_t TotalParentIterables = 0, size_t IndentLevel = 0, const char* indent = twoSpaces>
            struct Customize : public Unspecialized
            {
                /// Should return true if you put any output, else you should leave output unchanged
                static bool As(std::ostream & output, Context & context, const Object & object, const Value & value) { return false; }
            };

            template <typename Value, typename OpAnnotations = Annotate<>, typename Field = NoField, Statics statics = Statics::Excluded,
                bool PrettyPrint = false, size_t TotalParentIterables = 0, size_t IndentLevel = 0, const char* indent = twoSpaces>
            struct CustomizeType : public Unspecialized
            {
                /// Should return true if you put any output, else you should leave output unchanged
                static bool As(std::ostream & output, Context & context, const Value & value) { return false; }
            };

            template <typename Object, typename Value,
                size_t FieldIndex = NoFieldIndex, typename OpAnnotations = Annotate<>, typename Field = NoField, Statics statics = Statics::Excluded,
                bool PrettyPrint = false, size_t TotalParentIterables = 0, size_t IndentLevel = 0, const char* indent = twoSpaces>
            static constexpr bool HaveSpecialization =
                is_specialized<Customize<Object, Value, Field::Index, OpAnnotations, Field, statics,
                    PrettyPrint, TotalParentIterables, IndentLevel, indent>>::value || // Fully specialized
                is_specialized<Customize<Object, Value, Field::Index, OpAnnotations, Field>>::value || // Customize<5args> specialized
                is_specialized<Customize<Object, Value, Field::Index, OpAnnotations>>::value || // Customize<4args> specialized
                is_specialized<Customize<Object, Value, Field::Index>>::value || // Customize<3args> specialized
                is_specialized<Customize<Object, Value>>::value || // Customize<2args> specialized
                is_specialized<Customize<Object, Value, Field::Index, Annotate<>, Field>>::value || // Customize<5args>, OpAnnotations defaulted
                is_specialized<Customize<Object, Value, NoFieldIndex, OpAnnotations, Field>>::value || // Customize<5args>, FieldIndex defaulted
                is_specialized<Customize<Object, Value, NoFieldIndex, Annotate<>, Field>>::value || // Customize<5args>, both defaulted
                is_specialized<Customize<Object, Value, NoFieldIndex, OpAnnotations>>::value || // Customize<4args>, FieldIndex defaulted
                is_specialized<CustomizeType<Value, OpAnnotations, Field, statics,
                    PrettyPrint, TotalParentIterables, IndentLevel, indent>>::value || // Fully specialized
                is_specialized<CustomizeType<Value, OpAnnotations, Field>>::value || // CustomizeType<3args> specialized
                is_specialized<CustomizeType<Value, OpAnnotations>>::value || // CustomizeType<2args> specialized
                is_specialized<CustomizeType<Value>>::value || // CustomizeType<1arg> specialized
                is_specialized<CustomizeType<Value, Annotate<>, Field>>::value; // CustomizeType<3arg>, OpAnnotations defaulted
        }

        inline namespace StaticAffix
        {
            template <bool PrettyPrint, size_t IndentLevel, const char* indent = twoSpaces>
            struct IndentType { };
            
            template <bool PrettyPrint, size_t IndentLevel, const char* indent = twoSpaces>
            IndentType<PrettyPrint, IndentLevel, indent> Indent;

            template <bool PrettyPrint, size_t IndentLevel, const char* indent = twoSpaces>
            std::ostream & operator<<(std::ostream & os, const IndentType<PrettyPrint, IndentLevel, indent> &)
            {
                if constexpr ( IndentLevel > 0 && PrettyPrint )
                {
                    for ( size_t i=0; i<IndentLevel; i++ )
                        os << indent;
                }

                return os;
            }
            
            template <bool PrettyPrint, bool ContainsPrimitives, size_t IndentLevel, const char* indent = twoSpaces>
            struct ArrayPrefixType { };

            template <bool PrettyPrint, bool ContainsPrimitives, size_t IndentLevel, const char* indent = twoSpaces>
            ArrayPrefixType<PrettyPrint, ContainsPrimitives, IndentLevel, indent> ArrayPrefix;

            template <bool PrettyPrint, bool ContainsPrimitives, size_t IndentLevel, const char* indent = twoSpaces>
            std::ostream & operator<<(std::ostream & os, const ArrayPrefixType<PrettyPrint, ContainsPrimitives, IndentLevel, indent> &)
            {
                if constexpr ( !PrettyPrint )
                    os << "[";
                else if constexpr ( ContainsPrimitives )
                    os << "[ ";
                else
                    os << "[" << std::endl << Indent<PrettyPrint, IndentLevel, indent>;

                return os;
            }

            template <bool PrettyPrint, bool ContainsPrimitives, size_t IndentLevel, const char* indent = twoSpaces>
            struct ArraySuffixType { };

            template <bool PrettyPrint, bool ContainsPrimitives, size_t IndentLevel, const char* indent = twoSpaces>
            ArraySuffixType<PrettyPrint, ContainsPrimitives, IndentLevel, indent> ArraySuffix;

            template <bool PrettyPrint, bool ContainsPrimitives, size_t IndentLevel, const char* indent = twoSpaces>
            std::ostream & operator<<(std::ostream & os, const ArraySuffixType<PrettyPrint, ContainsPrimitives, IndentLevel, indent> &)
            {
                if constexpr ( !PrettyPrint )
                    os << "]";
                else if constexpr ( ContainsPrimitives )
                    os << " ]";
                else
                    os << std::endl << Indent<PrettyPrint, IndentLevel, indent> << "]";

                return os;
            }

            template <bool PrettyPrint, size_t IndentLevel, const char* indent = twoSpaces, Statics statics = Statics::Excluded, typename Object = void>
            struct ObjectPrefixType { };
                
            template <bool PrettyPrint, size_t IndentLevel, const char* indent = twoSpaces, Statics statics = Statics::Excluded, typename Object = void>
            ObjectPrefixType<PrettyPrint, IndentLevel, indent> ObjectPrefix;
                
            template <bool PrettyPrint, size_t IndentLevel, const char* indent, Statics statics, typename Object>
            std::ostream & operator<<(std::ostream & os, const ObjectPrefixType<PrettyPrint, IndentLevel, indent, statics, Object> &)
            {
                os << "{";
                return os;
            }

            template <bool PrettyPrint, size_t IndentLevel, const char* indent = twoSpaces, Statics statics = Statics::Excluded, typename Object = void>
            struct ObjectSuffixType { };
                
            template <bool PrettyPrint, size_t IndentLevel, const char* indent = twoSpaces, Statics statics = Statics::Excluded, typename Object = void>
            ObjectSuffixType<PrettyPrint, IndentLevel, indent, statics, Object> ObjectSuffix;
                
            template <bool PrettyPrint, size_t IndentLevel, const char* indent = twoSpaces, Statics statics = Statics::Excluded, typename Object = void>
            std::ostream & operator<<(std::ostream & os, const ObjectSuffixType<PrettyPrint, IndentLevel, indent, statics, Object> &)
            {
                if constexpr ( std::is_same<void, Object>::value )
                {
                    if constexpr ( PrettyPrint )
                        os << std::endl << Indent<PrettyPrint, IndentLevel, indent> << "}";
                    else
                        os << "}";
                }
                else
                {
                    constexpr bool NotEmpty =
                        statics == Statics::Only && Object::Class::TotalStaticFields > 0 ||
                        statics == Statics::Included && Object::Class::TotalFields > 0 ||
                        statics == Statics::Excluded && Object::Class::TotalFields > 0 && Object::Class::TotalStaticFields < Object::Class::TotalFields ||
                        Object::Supers::TotalSupers > 0;

                    if constexpr ( PrettyPrint && NotEmpty )
                        os << std::endl << Indent<PrettyPrint, IndentLevel, indent> << "}";
                    else
                        os << "}";
                }
                return os;
            }
                
            template <bool IsFirst, bool PrettyPrint, size_t IndentLevel, const char* indent = twoSpaces>
            struct FieldPrefixType { };
                
            template <bool IsFirst, bool PrettyPrint, size_t IndentLevel, const char* indent = twoSpaces>
            FieldPrefixType<IsFirst, PrettyPrint, IndentLevel, indent> FieldPrefix;
                
            template <bool IsFirst, bool PrettyPrint, size_t IndentLevel, const char* indent = twoSpaces>
            std::ostream & operator<<(std::ostream & os, const FieldPrefixType<IsFirst, PrettyPrint, IndentLevel, indent> &)
            {
                if constexpr ( PrettyPrint )
                {
                    if constexpr ( IsFirst )
                        os << std::endl << Indent<PrettyPrint, IndentLevel, indent>;
                    else 
                        os << "," << std::endl << Indent<PrettyPrint, IndentLevel, indent>;
                }
                else if constexpr ( !IsFirst )
                    os << ",";

                return os;
            }
                
            template <bool PrettyPrint>
            struct FieldNameValueSeparatorType { };

            template <bool PrettyPrint>
            FieldNameValueSeparatorType<PrettyPrint> FieldNameValueSeparator;
                
            template <bool PrettyPrint>
            std::ostream & operator<<(std::ostream & os, const FieldNameValueSeparatorType<PrettyPrint> &)
            {
                if constexpr ( PrettyPrint )
                    os << ": ";
                else
                    os << ":";

                return os;
            }
        };

        namespace Put
        {
            inline namespace Affix
            {
                template <bool PrettyPrint, const char* indent = twoSpaces>
                void Indent(std::ostream & os, size_t indentLevel)
                {
                    if constexpr ( PrettyPrint )
                    {
                        for ( size_t i=0; i<indentLevel; i++ )
                            os << indent;
                    }
                }
                
                template <bool PrettyPrint, bool ContainsPrimitives, const char* indent = twoSpaces>
                void ArrayPrefix(std::ostream & os, size_t indentLevel)
                {
                    if constexpr ( !PrettyPrint )
                        os << "[";
                    else if constexpr ( ContainsPrimitives )
                        os << "[ ";
                    else
                    {
                        os << "[" << std::endl;
                        Put::Indent<PrettyPrint, indent>(os, indentLevel);
                    }
                }

                template <bool PrettyPrint, bool ContainsPrimitives, const char* indent = twoSpaces>
                void ArraySuffix(std::ostream & os, size_t indentLevel)
                {
                    if constexpr ( !PrettyPrint )
                        os << "]";
                    else if constexpr ( ContainsPrimitives )
                        os << " ]";
                    else
                    {
                        os << std::endl;
                        Put::Indent<PrettyPrint, indent>(os, indentLevel);
                        os << "]";
                    }
                }
                
                template <bool PrettyPrint, const char* indent>
                void ObjectPrefix(std::ostream & os, size_t indentLevel)
                {
                    os << "{";
                }
                
                template <bool PrettyPrint, const char* indent = twoSpaces>
                void ObjectSuffix(std::ostream & os, bool isEmpty, size_t indentLevel)
                {
                    if ( PrettyPrint && !isEmpty )
                    {
                        os << std::endl;
                        Put::Indent<PrettyPrint, indent>(os, indentLevel);
                        os << "}";
                    }
                    else
                        os << "}";
                }
                
                template <bool PrettyPrint, const char* indent = twoSpaces>
                void FieldPrefix(std::ostream & os, bool isFirst, size_t indentLevel)
                {
                    if constexpr ( PrettyPrint )
                    {
                        if ( isFirst )
                        {
                            os << std::endl;
                            Put::Indent<PrettyPrint, indent>(os, indentLevel);
                        }
                        else
                        {
                            os << "," << std::endl;
                            Put::Indent<PrettyPrint, indent>(os, indentLevel);
                        }
                    }
                    else if ( !isFirst )
                        os << ",";
                }

                template <bool PrettyPrint, bool IsArray, bool ContainsPrimitives, size_t IndentLevel, const char* indent = twoSpaces>
                void NestedPrefix(std::ostream & os, bool isEmpty)
                {
                    if constexpr ( IsArray )
                    {
                        if ( isEmpty )
                            os << StaticAffix::ArrayPrefix<false, ContainsPrimitives, IndentLevel, indent>;
                        else
                            os << StaticAffix::ArrayPrefix<PrettyPrint, ContainsPrimitives, IndentLevel, indent>;
                    }
                    else
                    {
                        if ( isEmpty )
                            os << StaticAffix::ObjectPrefix<false, IndentLevel, indent>;
                        else
                            os << StaticAffix::ObjectPrefix<PrettyPrint, IndentLevel, indent>;
                    }
                }

                template <bool PrettyPrint, const char* indent = twoSpaces>
                void NestedPrefix(std::ostream & os, bool isArray, bool containsPrimitives, bool isEmpty, size_t indentLevel)
                {
                    if ( isArray )
                    {
                        if ( isEmpty )
                        {
                            if ( containsPrimitives )
                                Put::ArrayPrefix<false, true, indent>(os, indentLevel);
                            else
                                Put::ArrayPrefix<false, false, indent>(os, indentLevel);
                        }
                        else
                        {
                            if ( containsPrimitives )
                                Put::ArrayPrefix<PrettyPrint, true, indent>(os, indentLevel);
                            else
                                Put::ArrayPrefix<PrettyPrint, false, indent>(os, indentLevel);
                        }
                    }
                    else
                    {
                        if ( isEmpty )
                            Put::ObjectPrefix<false, indent>(os, indentLevel);
                        else
                            Put::ObjectPrefix<PrettyPrint, indent>(os, indentLevel);
                    }
                }
                
                template <bool PrettyPrint, bool IsArray, bool ContainsPrimitives, size_t IndentLevel, const char* indent = twoSpaces>
                void NestedSuffix(std::ostream & os, bool isEmpty)
                {
                    if constexpr ( IsArray )
                    {
                        if ( isEmpty )
                            os << StaticAffix::ArraySuffix<false, ContainsPrimitives, IndentLevel, indent>;
                        else
                            os << StaticAffix::ArraySuffix<PrettyPrint, ContainsPrimitives, IndentLevel, indent>;
                    }
                    else
                    {
                        if ( isEmpty )
                            os << StaticAffix::ObjectSuffix<false, IndentLevel, indent>;
                        else
                            os << StaticAffix::ObjectSuffix<PrettyPrint, IndentLevel, indent>;
                    }
                }
                
                template <bool PrettyPrint, const char* indent = twoSpaces>
                void NestedSuffix(std::ostream & os, bool isArray, bool containsPrimitives, bool isEmpty, size_t indentLevel)
                {
                    if ( isArray )
                    {
                        if ( isEmpty )
                        {
                            if ( containsPrimitives )
                                Put::ArraySuffix<false, true, indent>(os, indentLevel);
                            else
                                Put::ArraySuffix<false, false, indent>(os, indentLevel);
                        }
                        else
                        {
                            if ( containsPrimitives )
                                Put::ArraySuffix<PrettyPrint, true, indent>(os, indentLevel);
                            else
                                Put::ArraySuffix<PrettyPrint, false, indent>(os, indentLevel);
                        }
                    }
                    else
                    {
                        if ( isEmpty )
                            Put::ObjectSuffix<false, indent>(os, isEmpty, indentLevel);
                        else
                            Put::ObjectSuffix<PrettyPrint, indent>(os, isEmpty, indentLevel);
                    }
                }
                
                template <bool PrettyPrint, bool IsJsonField, bool NestedSeparator, size_t IndentLevel, const char* indent = twoSpaces>
                void Separator(std::ostream & os, bool isFirst)
                {
                    if constexpr ( IsJsonField )
                    {
                        if ( isFirst && PrettyPrint )
                            os << std::endl << StaticAffix::Indent<PrettyPrint, IndentLevel, indent>;
                        else if constexpr ( PrettyPrint )
                            os << "," << std::endl << StaticAffix::Indent<PrettyPrint, IndentLevel, indent>;
                        else if ( !isFirst )
                            os << ",";
                    }
                    else if ( !isFirst )
                    {
                        if constexpr ( NestedSeparator && PrettyPrint )
                            os << "," << std::endl << StaticAffix::Indent<PrettyPrint, IndentLevel, indent>;
                        else if constexpr ( PrettyPrint )
                            os << ", ";
                        else
                            os << ",";
                    }
                }
                
                template <bool PrettyPrint, bool IsJsonField, bool NestedSeparator, const char* indent = twoSpaces>
                void Separator(std::ostream & os, bool isFirst, size_t indentLevel)
                {
                    if constexpr ( IsJsonField )
                    {
                        if ( isFirst && PrettyPrint )
                        {
                            os << std::endl;
                            Put::Indent<PrettyPrint, indent>(os, indentLevel);
                        }
                        else if constexpr ( PrettyPrint )
                        {
                            os << "," << std::endl;
                            Put::Indent<PrettyPrint, indent>(os, indentLevel);
                        }
                        else if ( !isFirst )
                            os << ",";
                    }
                    else if ( !isFirst )
                    {
                        if constexpr ( NestedSeparator && PrettyPrint )
                        {
                            os << "," << std::endl;
                            Put::Indent<PrettyPrint, indent>(os, indentLevel);
                        }
                        else if constexpr ( PrettyPrint )
                            os << ", ";
                        else
                            os << ",";
                    }
                }
            };

            template <typename Annotations, typename Field, Statics statics,
                bool PrettyPrint, size_t TotalParentIterables, size_t IndentLevel, const char* indent, typename Object, typename Value>
            static constexpr inline bool Customization(std::ostream & os, Context & context, const Object & obj, const Value & value)
            {
                if constexpr ( is_specialized<Customize<Object, Value, Field::Index, Annotations, Field, statics,
                    PrettyPrint, TotalParentIterables, IndentLevel, indent>>::value )
                {
                    return Customize<Object, Value, Field::Index, Annotations, Field, statics,
                        PrettyPrint, TotalParentIterables, IndentLevel, indent>::As(os, context, obj, value); // Customize fully specialized
                }
                else if constexpr ( is_specialized<Customize<Object, Value, Field::Index, Annotations, Field>>::value )
                    return Customize<Object, Value, Field::Index, Annotations, Field>::As(os, context, obj, value); // Five Customize arguments specialized
                else if constexpr ( is_specialized<Customize<Object, Value, Field::Index, Annotations>>::value )
                    return Customize<Object, Value, Field::Index, Annotations>::As(os, context, obj, value); // Four Customize arguments specialized
                else if constexpr ( is_specialized<Customize<Object, Value, Field::Index>>::value )
                    return Customize<Object, Value, Field::Index>::As(os, context, obj, value); // Three Customize arguments specialized
                else if constexpr ( is_specialized<Customize<Object, Value>>::value )
                    return Customize<Object, Value>::As(os, context, obj, value); // Two Customize arguments specialized
                else if constexpr ( is_specialized<Customize<Object, Value, Field::Index, Annotate<>, Field>>::value )
                    return Customize<Object, Value, Field::Index, Annotate<>, Field>::As(os, context, obj, value); // Customize<5args>, Annotations defaulted
                else if constexpr ( is_specialized<Customize<Object, Value, NoFieldIndex, Annotations, Field>>::value )
                    return Customize<Object, Value, NoFieldIndex, Annotations, Field>::As(os, context, obj, value); // Customize<5args>, FieldIndex defaulted
                else if constexpr ( is_specialized<Customize<Object, Value, NoFieldIndex, Annotate<>, Field>>::value )
                    return Customize<Object, Value, NoFieldIndex, Annotate<>, Field>::As(os, context, obj, value); // Customize<5args>, two args defaulted
                else if constexpr ( is_specialized<Customize<Object, Value, NoFieldIndex, Annotations>>::value )
                    return Customize<Object, Value, NoFieldIndex, Annotations>::As(os, context, obj, value); // Customize<4args>, FieldIndex defaulted
                else if constexpr ( is_specialized<CustomizeType<Value, Annotations, Field, statics,
                    PrettyPrint, TotalParentIterables, IndentLevel, indent>>::value )
                {
                    return CustomizeType<Value, Annotations, Field, statics,
                        PrettyPrint, TotalParentIterables, IndentLevel, indent>::As(os, context, value); // CustomizeType fully specialized
                }
                else if constexpr ( is_specialized<CustomizeType<Value, Annotations, Field>>::value )
                    return CustomizeType<Value, Annotations, Field>::As(os, context, value); // Three CustomizeType arguments specialized
                else if constexpr ( is_specialized<CustomizeType<Value, Annotations>>::value )
                    return CustomizeType<Value, Annotations>::As(os, context, value); // Two CustomizeType arguments specialized
                else if constexpr ( is_specialized<CustomizeType<Value>>::value )
                    return CustomizeType<Value>::As(os, context, value); // One CustomizeType argument specialized
                else if constexpr ( is_specialized<CustomizeType<Value, Annotate<>, Field>>::value )
                    return CustomizeType<Value, Annotate<>, Field>::As(os, context, value); // CustomizeType<3args>, Annotations defaulted
                else
                    return false;
            }

            static void String(std::ostream & os, const std::string & str)
            {
                os << "\"";
                for ( size_t i=0; i<str.size(); i++ )
                {
                    switch ( str[i] )
                    {
                    case '\"': os << "\\\""; break;
                    case '\\': os << "\\\\"; break;
                    case '/': os << "\\/"; break;
                    case '\b': os << "\\b"; break;
                    case '\f': os << "\\f"; break;
                    case '\n': os << "\\n"; break;
                    case '\r': os << "\\r"; break;
                    case '\t': os << "\\t"; break;
                    default: os << str[i]; break;
                    }
                }
                os << "\"";
            }

            template <typename T>
            static constexpr void String(std::ostream & os, const T & t)
            {
                std::stringstream ss;
                ss << t;
                Put::String(os, ss.str());
            }
            
            template <typename Annotations, bool PrettyPrint, const char* indent>
            static constexpr void Value(std::ostream & os, Context & context,
                size_t totalParentIterables, size_t indentLevel, const Generic::Value & value)
            {
                switch ( value.type() )
                {
                    case Generic::Value::Type::Boolean:
                        os << (value.boolean() ? "true" : "false");
                        break;
                    case Generic::Value::Type::Number:
                        os << value.number();
                        break;
                    case Generic::Value::Type::String:
                        os << "\"" << value.string() << "\"";
                        break;
                    case Generic::Value::Type::Object:
                    case Generic::Value::Type::BoolArray:
                    case Generic::Value::Type::NumberArray:
                    case Generic::Value::Type::StringArray:
                    case Generic::Value::Type::ObjectArray:
                    case Generic::Value::Type::MixedArray:
                        Put::Iterable<Annotations, PrettyPrint, indent>(os, context, totalParentIterables, indentLevel, value);
                        break;
                }
            }

            template <typename Annotations, typename Field, Statics statics,
                bool PrettyPrint, size_t TotalParentIterables, size_t IndentLevel, const char* indent, typename Object, typename T>
            static constexpr void Value(std::ostream & os, Context & context, const Object & obj, const T & value)
            {
                if constexpr ( Customizers::HaveSpecialization<Object, T, Field::Index, Annotations, Field, statics,
                    PrettyPrint, TotalParentIterables, IndentLevel, indent> )
                {
                    if ( Put::Customization<Annotations, Field, statics,
                        PrettyPrint, TotalParentIterables, IndentLevel, indent, Object, T>(os, context, obj, value) )
                    {
                        return;
                    }
                }

                if constexpr ( is_pointable<T>::value )
                {
                    if ( value == nullptr )
                        os << "null";
                    else
                        Put::Value<Annotations, Field, statics, PrettyPrint, TotalParentIterables, IndentLevel, indent, Object>(os, context, obj, *value);
                }
                else if constexpr ( std::is_base_of<Generic::Value, T>::value )
                    Put::Value<Annotations, PrettyPrint, indent>(os, context, TotalParentIterables, IndentLevel+1, (const Generic::Value &)value);
                else if constexpr ( is_iterable<T>::value )
                    Put::Iterable<Annotations, Field, statics, PrettyPrint, TotalParentIterables, IndentLevel, indent, Object>(os, context, obj, value);
                else if constexpr ( Field::template HasAnnotation<IsRoot> )
                    Put::Object<Annotations, statics, PrettyPrint, IndentLevel+TotalParentIterables, indent, T>(os, context, value);
                else if constexpr ( Field::template HasAnnotation<Reflect::Reflected> )
                    Put::Object<Annotations, statics, PrettyPrint, IndentLevel+TotalParentIterables+1, indent, T>(os, context, value);
                else if constexpr ( Field::template HasAnnotation<Json::String> )
                    Put::String(os, value);
                else if constexpr ( Field::template HasAnnotation<Json::EnumInt> )
                    os << (typename promote_char<typename std::underlying_type<T>::type>::type)value;
                else if constexpr ( is_bool<T>::value )
                    os << (value ? "true" : "false");
                else
                    os << (typename promote_char<T>::type)value;
            }
            
            template <typename Annotations, typename Field, Statics statics,
                bool PrettyPrint, size_t TotalParentIterables, size_t IndentLevel, const char* indent, typename Object, typename T, typename Key>
            static constexpr void Value(std::ostream & os, Context & context, const Object & obj, const std::pair<Key, T> & pair)
            {
                Put::String(os, pair.first);
                os << FieldNameValueSeparator<PrettyPrint>;
                Put::Value<Annotations, Field, statics, PrettyPrint, TotalParentIterables, IndentLevel, indent, Object>(os, context, obj, pair.second);
            }

            template <typename Annotations, typename Field, Statics statics,
                bool PrettyPrint, size_t TotalParentIterables, size_t IndentLevel, const char* indent, typename Object, typename IterableValue = uint_least8_t>
            static constexpr void Iterable(std::ostream & os, Context & context, const Object & obj, const IterableValue & iterable)
            {
                using Element = typename element_type<IterableValue>::type;
                constexpr bool ContainsIterables = is_iterable<typename pair_rhs<Element>::type>::value;
                constexpr bool ContainsPrimitives = !Field::template HasAnnotation<Reflect::Reflected> && !ContainsIterables;
                constexpr bool ContainsPairs = is_pair<Element>::value;
                
                size_t i=0;
                Put::NestedPrefix<PrettyPrint, !ContainsPairs, ContainsPrimitives, IndentLevel+TotalParentIterables+2, indent>(os, IsEmpty(iterable));
                if constexpr ( is_stl_iterable<IterableValue>::value )
                {
                    for ( auto & element : iterable )
                    {
                        Put::Separator<PrettyPrint, ContainsPairs, ContainsIterables, IndentLevel+TotalParentIterables+2, indent>(os, 0 == i++);
                        Put::Value<Annotations, Field, statics, PrettyPrint, TotalParentIterables+1, IndentLevel, indent, Object>(os, context, obj, element);
                    }
                }
                else if constexpr ( is_adaptor<IterableValue>::value )
                {
                    const auto & sequenceContainer = get_underlying_container(iterable);
                    for ( auto it = sequenceContainer.begin(); it != sequenceContainer.end(); ++it )
                    {
                        Put::Separator<ContainsPairs, ContainsIterables, IndentLevel+TotalParentIterables+2, indent>(os, 0 == i++);
                        Put::Value<Annotations, Field, statics, PrettyPrint, TotalParentIterables+1, IndentLevel, indent, Object>(os, context, obj, *it);
                    }
                }
                else if constexpr ( std::is_array<IterableValue>::value && std::extent<Field::Type>::value > 0 )
                {
                    for ( ; i<std::extent<Field::Type>::value; i++ )
                    {
                        Put::Separator<PrettyPrint, ContainsPairs, ContainsIterables, IndentLevel+TotalParentIterables+2, indent>(os, 0 == i);
                        Put::Value<Annotations, Field, statics, PrettyPrint, TotalParentIterables+1, IndentLevel, indent, Object>(os, context, obj, iterable[i]);
                    }
                }
                Put::NestedSuffix<PrettyPrint, !ContainsPairs, ContainsPrimitives, IndentLevel+TotalParentIterables+1, indent>(os, IsEmpty(iterable));
            }

            template <typename Annotations, bool PrettyPrint, const char* indent>
            static constexpr void Iterable(std::ostream & os, Context & context,
                size_t totalParentIterables, size_t indentLevel, const Generic::Value & iterable)
            {
                bool isObject = iterable.type() == Generic::Value::Type::Object;
                bool containsPrimitives = iterable.type() == Generic::Value::Type::BoolArray ||
                    iterable.type() == Generic::Value::Type::NumberArray || iterable.type() == Generic::Value::Type::StringArray;
                bool isEmpty = (isObject && iterable.object().empty()) || (!isObject && iterable.arraySize() == 0);

                size_t i=0;
                Put::NestedPrefix<PrettyPrint, indent>(os, !isObject, containsPrimitives, isEmpty, indentLevel+totalParentIterables+1);
                switch ( iterable.type() )
                {
                    case Generic::Value::Type::Object:
                    {
                        const std::map<std::string, std::shared_ptr<Generic::Value>> & obj = iterable.object();
                        bool isFirst = true;
                        for ( const auto & field : obj )
                        {
                            Put::FieldPrefix<PrettyPrint, indent>(os, isFirst, indentLevel+totalParentIterables+1);
                            Put::String(os, field.first);
                            os << FieldNameValueSeparator<PrettyPrint>;
                            Put::Value<Annotations, PrettyPrint, indent>(os, context, 0, indentLevel+totalParentIterables+1, (Generic::Value &)*field.second);
                            isFirst = false;
                        }
                    }
                    break;
                    case Generic::Value::Type::BoolArray:
                    {
                        const std::vector<bool> & array = iterable.boolArray();
                        for ( const auto & element : array )
                        {
                            Put::Separator<PrettyPrint, false, false, indent>(os, 0 == i++, indentLevel+totalParentIterables+2);
                            os << (element ? "true" : "false");
                        }
                    }
                    break;
                    case Generic::Value::Type::NumberArray:
                    {
                        const std::vector<std::string> & array = iterable.numberArray();
                        for ( const auto & element : array )
                        {
                            Put::Separator<PrettyPrint, false, false, indent>(os, 0 == i++, indentLevel+totalParentIterables+2);
                            os << element;
                        }
                    }
                    break;
                    case Generic::Value::Type::StringArray:
                    {
                        const std::vector<std::string> & array = iterable.stringArray();
                        for ( const auto & element : array )
                        {
                            Put::Separator<PrettyPrint, false, false, indent>(os, 0 == i++, indentLevel+totalParentIterables+2);
                            os << element;
                        }
                    }
                    break;
                    case Generic::Value::Type::ObjectArray:
                    {
                        const std::vector<std::map<std::string, std::shared_ptr<Generic::Value>>> & array = iterable.objectArray();
                        for ( const std::map<std::string, std::shared_ptr<Generic::Value>> & obj : array )
                        {
                            Put::Separator<PrettyPrint, false, true, indent>(os, 0 == i++, indentLevel+totalParentIterables+2);
                            bool isFirst = true;
                            for ( const auto & field : obj )
                            {
                                Put::FieldPrefix<PrettyPrint, indent>(os, isFirst, indentLevel+1);
                                Put::String(os, field.first);
                                os << FieldNameValueSeparator<PrettyPrint>;
                                Put::Value<Annotations, PrettyPrint, indent>(os, context, totalParentIterables+1, indentLevel, (Generic::Value &)field.second);
                                isFirst = false;
                            }
                        }
                    }
                    break;
                    case Generic::Value::Type::MixedArray:
                    {
                        const std::vector<std::shared_ptr<Generic::Value>> & array = iterable.mixedArray();
                        for ( const std::shared_ptr<Generic::Value> & element : array )
                        {
                            Put::Separator<PrettyPrint, false, true, indent>(os, 0 == i++, indentLevel+totalParentIterables+2);
                            Put::Value<Annotations, PrettyPrint, indent>(os, context, totalParentIterables, indentLevel, *element);
                        }
                    }
                    break;
                }
                Put::NestedSuffix<PrettyPrint, indent>(os, !isObject, containsPrimitives, isEmpty, indentLevel+totalParentIterables);
            }

            template <typename Annotations, typename FieldClass, Statics statics,
                bool PrettyPrint, size_t IndentLevel, const char* indent, typename Object>
            static constexpr void Field(std::ostream & os, Context & context, const Object & obj, const char* fieldName, const typename FieldClass::Type & value)
            {
                if constexpr ( matches_statics<FieldClass::IsStatic, statics>::value )
                {
                    os << StaticAffix::FieldPrefix<FieldClass::Index == FirstIndex<statics, Object>(), PrettyPrint, IndentLevel+1, indent>;
                    Put::String(os, fieldName);
                    os << FieldNameValueSeparator<PrettyPrint>;
                    Put::Value<Annotations, FieldClass, statics, PrettyPrint, 0, IndentLevel, indent, Object>(os, context, obj, value);
                }
            }
            
            template <typename Annotations, Statics statics, bool PrettyPrint, size_t IndentLevel, const char* indent, typename Object>
            static constexpr void Fields(std::ostream & os, Context & context, const Object & obj)
            {
                Object::Class::ForEachField(obj, [&](auto & field, auto & value)
                {
                    using Field = typename std::remove_reference<decltype(field)>::type;
                    Put::Field<Annotations, Field, statics, PrettyPrint, IndentLevel, indent, Object>(os, context, obj, field.name, value);
                });
            }

            template <typename Annotations, size_t SuperIndex, typename T, Statics statics,
                bool PrettyPrint, size_t IndentLevel, const char* indent, typename Object>
            static constexpr void Super(std::ostream & os, Context & context, const Object & obj, const std::string & superFieldName)
            {
                os << StaticAffix::FieldPrefix<SuperIndex == 0, PrettyPrint, IndentLevel+1, indent>;
                Put::String(os, superFieldName);
                os << FieldNameValueSeparator<PrettyPrint>;
                Put::Object<Annotations, statics, PrettyPrint, IndentLevel+1, indent, T>(os, context, obj);
            }
            
            template <typename Annotations, Statics statics, bool PrettyPrint, size_t IndentLevel, const char* indent, typename Object>
            static constexpr void Supers(std::ostream & os, Context & context, const Object & obj)
            {
                Object::Supers::ForEach(obj, [&](auto index, auto & superObj)
                {
                    using Super = typename std::remove_reference<decltype(superObj)>::type;
                    Put::Super<Annotations, decltype(index)::Index, Super, statics, PrettyPrint, IndentLevel, indent, Object>(
                        os, context, obj, superTypeToJsonFieldName<Super>());
                });
            }

            template <typename Annotations, Statics statics, bool PrettyPrint, size_t IndentLevel, const char* indent, typename T>
            static constexpr void Object(std::ostream & os, Context & context, const T & obj)
            {
                os << StaticAffix::ObjectPrefix<PrettyPrint, IndentLevel, indent, statics, T>;
                Put::Fields<Annotations, statics, PrettyPrint, IndentLevel, indent, T>(os, context, obj);
                Put::Supers<Annotations, statics, PrettyPrint, IndentLevel, indent, T>(os, context, obj);
                os << StaticAffix::ObjectSuffix<PrettyPrint, IndentLevel, indent, statics, T>;
            }
        }
        
        template <typename Annotations = Annotate<>, Statics statics = Statics::Excluded,
            bool PrettyPrint = false, size_t IndentLevel = 0, const char* indent = twoSpaces, typename Object = uint_least8_t>
        class ReflectedObject
        {
        public:
            ReflectedObject(const Object & obj, std::shared_ptr<Context> context) : obj(obj), context(context) {}

            const Object & obj;
            std::shared_ptr<Context> context;
            
            constexpr std::ostream & put(std::ostream & os)
            {
                if ( context == nullptr )
                    context = std::shared_ptr<Context>(new Context());

                Put::Value<Annotations, ReflectedField<Object>, statics, PrettyPrint, 0, IndentLevel, indent, Object, Object>(os, *context, obj, obj);
                return os;
            }
        };
        
        template <Statics statics = Statics::Excluded, typename Annotations = Annotate<>, bool PrettyPrint = false,
            size_t IndentLevel = 0, const char* indent = twoSpaces, typename T = uint_least8_t>
        std::ostream & operator<<(std::ostream & os, Output::ReflectedObject<Annotations, statics, PrettyPrint, IndentLevel, indent, T> object)
        {
            return object.put(os);
        }

        template <Statics statics = Statics::Excluded, typename Annotations = Annotate<>,
            size_t IndentLevel = 0, const char* indent = twoSpaces, typename T = uint_least8_t>
        constexpr Output::ReflectedObject<Annotations, statics, false, IndentLevel, indent, T> out(const T & t, std::shared_ptr<Context> context = nullptr)
        {
            return Output::ReflectedObject<Annotations, statics, false, IndentLevel, indent, T>(t, context);
        }
    
        template <Statics statics = Statics::Excluded, typename Annotations = Annotate<>,
            size_t IndentLevel = 0, const char* indent = twoSpaces, typename T = uint_least8_t>
        constexpr Output::ReflectedObject<Annotations, statics, true, IndentLevel, indent, T> pretty(const T & t, std::shared_ptr<Context> context = nullptr)
        {
            return Output::ReflectedObject<Annotations, statics, true, IndentLevel, indent, T>(t, context);
        }

        std::ostream & operator<<(std::ostream & os, const Generic::Value & value)
        {
            Put::Value<Annotate<>, true, twoSpaces>(os, context, 0, 0, value);
            return os;
        }
    };
    
    inline namespace Input
    {
        inline namespace Customizers
        {
            template <typename Object, typename Value, size_t FieldIndex = NoFieldIndex, typename OpAnnotations = Annotate<>, typename Field = NoField>
            struct Customize : public Unspecialized
            {
                /// return false if you wish for the input to be re-parsed by the default JSON code, else return true
                /// For invalid input you can throw an exception to end parsing immediately, or return true to continue parsing
                static bool As(std::istream & input, Context & context, const Object & object, Value & value) { return false; }
            };
            
            template <typename Value, typename OpAnnotations = Annotate<>, typename Field = NoField>
            struct CustomizeType : public Unspecialized
            {
                /// Should return true if you put any output, else you should leave output unchanged
                static bool As(std::istream & input, Context & context, const Value & value) { return false; }
            };

            template <typename Object, typename Value, size_t FieldIndex = NoFieldIndex, typename OpAnnotations = Annotate<>, typename Field = NoField>
            static constexpr bool HaveSpecialization =
                is_specialized<Customize<Object, Value, FieldIndex, OpAnnotations, Field>>::value || // Fully specialized
                is_specialized<Customize<Object, Value, FieldIndex, OpAnnotations>>::value || // Customize<4args> specialized
                is_specialized<Customize<Object, Value, FieldIndex>>::value || // Customize<3args> specialized
                is_specialized<Customize<Object, Value>>::value || // Customize<2args> specialized
                is_specialized<Customize<Object, Value, FieldIndex, Annotate<>, Field>>::value || // Customize<5args>, OpAnnotations defaulted
                is_specialized<Customize<Object, Value, NoFieldIndex, OpAnnotations, Field>>::value || // Customize<5args>, FieldIndex defaulted
                is_specialized<Customize<Object, Value, NoFieldIndex, Annotate<>, Field>>::value || // Customize<5args>, both defaulted
                is_specialized<Customize<Object, Value, NoFieldIndex, OpAnnotations>>::value || // Customize<4args>, FieldIndex defaulted
                is_specialized<CustomizeType<Value, OpAnnotations, Field>>::value || // Fully specialized
                is_specialized<CustomizeType<Value, OpAnnotations>>::value || // CustomizeType<2args> specialized
                is_specialized<CustomizeType<Value>>::value || // CustomizeType<1arg> specialized
                is_specialized<CustomizeType<Value, Annotate<>, Field>>::value; // CustomizeType<3args>, OpAnnotations defaulted
        }

        inline namespace Exceptions
        {
            static constexpr const char unicodeEscapeSequence[] = "\\uHHHH (where H's are hex characters)";

            class InvalidNumericCharacter : public Exception
            {
            public:
                InvalidNumericCharacter(char invalidCharacter, const char* expected)
                    : Exception((std::string("Invalid numeric character: \"") + invalidCharacter + "\" expected: " + expected).c_str()) {}
            };

            class InvalidSecondDecimal : public Exception
            {
            public:
                InvalidSecondDecimal()
                    : Exception(std::string("Invalid second decimal, expected: [0-9], \",\", or \"}\"").c_str()) {}
            };

            class InvalidEscapeSequence : public Exception
            {
            public:
                InvalidEscapeSequence(const char* escapeSequence, const char* expected)
                    : Exception((std::string("Invalid escape sequence: \"") + escapeSequence + "\", expected: " + expected).c_str()) {}
            };

            class UnexpectedLineEnding : public Exception
            {
            public:
                UnexpectedLineEnding(const char* lineEnding) : Exception(lineEnding) {}
            };

            class FieldNameUnexpectedLineEnding : public UnexpectedLineEnding
            {
            public:
                FieldNameUnexpectedLineEnding(const UnexpectedLineEnding & e) : UnexpectedLineEnding(
                    (std::string("Expected field name close quote, found line ending (\"") + e.what() + "\")").c_str()) {}
            };

            class UnexpectedInputEnd : public Exception
            {
            public:
                UnexpectedInputEnd(const std::string & expected) : Exception((std::string("Expected ") + expected + " but found end of input").c_str()) {}
            };

            class StreamReadFail : public Exception
            {
            public:
                StreamReadFail() : Exception("Attempt to read from stream failed (std::ios::fail() == true)") {}
            };

            class StreamUngetFail : public Exception
            {
            public:
                StreamUngetFail(char c) : Exception((std::string("Attempt to unread last character (") + c + ") resulted in failure").c_str()) {}
            };

            template <typename Field>
            class UnexpectedFieldValue : public Exception
            {
            public:
                template <typename Field>
                static std::string getExpectation(Field field)
                {
                    std::string expectation;
                    if constexpr ( Field::IsPointer )
                        return "\"null\""; // TODO: More handling for pointers
                    else if constexpr ( Field::IsBool )
                        return "true or false";
                    else if constexpr ( Field::IsArray )
                        return "JSON Array";
                    else if constexpr ( Field::IsObject )
                        return "JSON Object";
                    else if constexpr ( Field::template HasAnnotation<Json::String> )
                        return "JSON String";
                    else
                        return "TODO: Implement more expectations";
                }

                UnexpectedFieldValue(Field field)
                    : Exception((
                        std::string("Unexpected value for field: \"") + field.name + "\". Expected: "
                        + getExpectation<Field>(field)
                    ).c_str()) {}

                UnexpectedFieldValue(Field field, const char* fieldValue)
                    : Exception((
                        std::string("Unexpected value: \"") + fieldValue + "\" for field: \"" + field.name + "\". Expected: "
                        + getExpectation<Field>(field)
                    ).c_str()) {}
            };

            class InvalidUnknownFieldValue : public Exception
            {
            public:
                InvalidUnknownFieldValue() : Exception("Expected field value (string, number, object, array, true, false, or null)") {}
            };

            class ArraySizeExceeded : public Exception
            {
            public:
                ArraySizeExceeded() : Exception("Array size exceeded!") {}
            };
        };

        inline namespace Cache
        {
            extern std::hash<std::string> strHash;

            extern std::map<std::type_index, std::multimap<size_t, JsonField>> classToNameHashToJsonField;

            template <typename T>
            static std::multimap<size_t, JsonField> & getClassFieldCache(const T & t)
            {
                using Class = typename T::Class;
                using Supers = typename T::Supers;
                auto found = classToNameHashToJsonField.find(std::type_index(typeid(T)));
                if ( found == classToNameHashToJsonField.end() )
                {
                    auto inserted = classToNameHashToJsonField.insert(std::pair<std::type_index, std::multimap<size_t, JsonField>>(
                        std::type_index(typeid(T)), std::multimap<size_t, JsonField>()));

                    if ( !inserted.second )
                        throw Exception("Failed to create cache for class!");

                    if constexpr ( Class::TotalFields > 0 )
                    {
                        for ( size_t fieldIndex = 0; fieldIndex < Class::TotalFields; fieldIndex++ )
                        {
                            inserted.first->second.insert(std::pair<size_t, JsonField>(
                                strHash(Class::Fields[fieldIndex].name), JsonField(fieldIndex, JsonField::Type::Regular, Class::Fields[fieldIndex].name)));
                        }
                    }

                    if constexpr ( Supers::TotalSupers > 0 )
                    {
                        for ( size_t superIndex = 0; superIndex < Supers::TotalSupers; superIndex++ )
                        {
                            Supers::At(t, superIndex, [&](auto & superObj) {
                                using Super = typename std::remove_reference<decltype(superObj)>::type;
                                std::string superTypeFieldName = superTypeToJsonFieldName<Super>();
                                inserted.first->second.insert(std::pair<size_t, JsonField>(
                                    strHash(superTypeFieldName), JsonField(superIndex, JsonField::Type::SuperClass, superTypeFieldName)));
                            });
                        }
                    }
                            
                    return inserted.first->second;
                }
                return found->second;
            }

            template <typename T>
            static JsonField* getJsonField(T & t, const std::string & fieldName)
            {
                std::multimap<size_t, JsonField> & fieldNameToJsonField = getClassFieldCache(t);
                size_t fieldNameHash = strHash(fieldName);
                auto fieldHashMatches = fieldNameToJsonField.equal_range(fieldNameHash);
                for ( auto it = fieldHashMatches.first; it != fieldHashMatches.second; ++it )
                {
                    if ( it->second.name.compare(fieldName) == 0 )
                        return &it->second;
                }
                return nullptr;
            }

            static void putClassFieldCache(std::ostream & os)
            {
                os << "{" << std::endl;
                bool hasPrevPair = false;
                for ( auto & pair : classToNameHashToJsonField )
                {
                    if ( hasPrevPair )
                        os << "  }," << std::endl;

                    os << "  \"" << simplifyTypeStr(pair.first.name()) << "\": {" << std::endl;
                    bool hasPrevFieldNameToJsonField = false;
                    for ( auto & fieldNameToJsonField : pair.second )
                    {
                        if ( hasPrevFieldNameToJsonField )
                            os << "    }," << std::endl;

                        os << "    \"" << fieldNameToJsonField.first << "\": {" << std::endl
                            << "      \"index\": " << fieldNameToJsonField.second.index << "," << std::endl
                            << "      \"type\": "
                            << (fieldNameToJsonField.second.type == JsonField::Type::Regular ? "\"Regular\"" : "\"SuperClass\"")
                            << "," << std::endl
                            << "      \"name\": \"" << fieldNameToJsonField.second.name << "\"" << std::endl;

                        hasPrevFieldNameToJsonField = true;
                    }
                    if ( hasPrevFieldNameToJsonField )
                        os << "    }" << std::endl;
                    hasPrevPair = true;
                }
                if ( hasPrevPair )
                    os << "  }" << std::endl;
                os << "}" << std::endl;
            }

            #define ENABLE_JSON_INPUT \
            std::hash<std::string> Json::strHash; \
            std::map<std::type_index, std::multimap<size_t, Json::Generic::JsonField>> Json::classToNameHashToJsonField
        };

        class Checked
        {
        public:
            static inline void peek(std::istream & is, char & c, const char* expectedDescription)
            {
                int character = is.peek();
                if ( !is.good() )
                {
                    if ( is.eof() )
                        throw UnexpectedInputEnd(expectedDescription);
                    else
                        throw StreamReadFail();
                }
                c = (char)character;
            }
            
            static inline bool tryGet(std::istream & is, int character, const char* expectedDescription)
            {
                is >> std::ws;
                if ( is.good() )
                {
                    int c = is.peek();
                    if ( is.good() )
                    {
                        if ( c == character )
                        {
                            is.ignore();
                            if ( is.good() )
                                return true;
                        }
                        else
                            return false;
                    }
                }
                if ( is.eof() )
                    throw UnexpectedInputEnd(expectedDescription);
                else
                    throw StreamReadFail();
            }
            
            template <bool usePrimary>
            static constexpr inline bool tryGet(std::istream & is, int character, int secondaryCharacter,
                const char* expectedDescription, const char* secondaryDescription)
            {
                if ( usePrimary )
                    return tryGet(is, character, expectedDescription);
                else
                    return tryGet(is, secondaryCharacter, secondaryDescription);
            }

            static bool get(std::istream & is, char trueChar, char falseChar, const char* expectedDescription)
            {
                char c = '\0';
                is >> c;
                if ( !is.good() )
                {
                    if ( is.eof() )
                        throw UnexpectedInputEnd(expectedDescription);
                    else
                        throw StreamReadFail();
                }
                else if ( c == trueChar )
                    return true;
                else if ( c == falseChar )
                    return false;
                else
                    throw Exception((std::string("Expected: ") + expectedDescription).c_str());
            }

            static inline void get(std::istream & is, char & c, const char* expectedDescription)
            {
                is >> c;
                if ( !is.good() )
                {
                    if ( is.eof() )
                        throw UnexpectedInputEnd(expectedDescription);
                    else
                        throw StreamReadFail();
                }
            }
            
            template <bool usePrimary>
            static constexpr inline char get(std::istream & is, char trueChar, char falseChar, char secondaryFalseChar,
                const char* expectedDescription, const char* secondaryDescription)
            {
                if constexpr ( usePrimary )
                    return get(is, trueChar, falseChar, expectedDescription);
                else
                    return get(is, trueChar, secondaryFalseChar, secondaryDescription);
            }

            template <bool usePrimary>
            static constexpr inline void get(std::istream & is, char & c, const char* expectedDescription, const char* secondaryDescription)
            {
                if constexpr ( usePrimary )
                    get(is, c, expectedDescription);
                else
                    get(is, c, secondaryDescription);
            }

            template <bool usePrimary>
            static constexpr inline void get(std::istream & is, char & c, int expectedChar, int secondaryChar,
                const char* expectedDescription, const char* secondaryDescription)
            {
                if constexpr ( usePrimary )
                    get(is, c, expectedChar, expectedDescription);
                else
                    get(is, c, secondaryChar, secondaryDescription);
            }

            static inline bool unget(std::istream & is, char ungetting)
            {
                is.unget();
                if ( !is.good() )
                    throw StreamUngetFail(ungetting);

                return true;
            }

            static inline void escapeSequenceGet(std::istream & is, char & c, const char* hexEscapeSequence)
            {
                is >> c;
                if ( !is.good() )
                {
                    if ( is.eof() )
                        throw InvalidEscapeSequence((std::string(hexEscapeSequence)).c_str(), unicodeEscapeSequence);
                    else
                        throw StreamReadFail();
                }
            }

            static inline void consumeWhitespace(std::istream & is, const char* expectedDescription)
            {
                is >> std::ws;
                if ( !is.good() )
                {
                    if ( is.eof() )
                        throw UnexpectedInputEnd(expectedDescription);
                    else
                        throw StreamReadFail();
                }
            }

            template <bool usePrimary>
            static constexpr inline void consumeWhitespace(std::istream & is, const char* expectedDescription, const char* secondaryDescription)
            {
                if constexpr ( usePrimary )
                    consumeWhitespace(is, expectedDescription);
                else
                    consumeWhitespace(is, secondaryDescription);
            }
        };

        namespace Consume
        {
            template <bool InArray>
            static constexpr void Null(std::istream & is, char & c)
            {
                Checked::consumeWhitespace(is, "completion of field value");
                int expectation[] = { 'n', 'u', 'l', 'l' };
                for ( size_t i=0; i<4; i++ )
                    Checked::get(is, c, expectation[i], "completion of field value");

                Checked::consumeWhitespace(is, "\",\" or \"}\"");
                Checked::peek(is, c, "\",\" or \"}\"");
                if ( InArray && c != ',' && c != ']' )
                    throw Exception("Expected: \",\" or \"]\"");
                else if ( !InArray && c != ',' && c != '}' )
                    throw Exception("Expected: \",\" or \"}\"");
            }

            template <bool InArray>
            static constexpr void Null(std::istream & is, char & c, std::stringstream & ss)
            {
                Consume::Null<InArray>(is, c);
                ss << "null";
            }

            template <bool InArray>
            static constexpr bool TryNull(std::istream & is, char & c)
            {
                Checked::consumeWhitespace(is, "null or field value");
                Checked::peek(is, c, "null or field value");
                if ( c == 'n' )
                {
                    int expectation[] = { 'n', 'u', 'l', 'l' };
                    for ( size_t i=0; i<4; i++ )
                        Checked::get(is, c, expectation[i], "completion of \"null\"");

                    Checked::consumeWhitespace(is, "\",\" or \"}\"");
                    Checked::peek(is, c, "\",\" or \"}\"");
                    if ( InArray && c != ',' && c != ']' )
                        throw Exception("Expected: \",\" or \"]\"");
                    else if ( !InArray && c != ',' && c != '}' )
                        throw Exception("Expected: \",\" or \"}\"");
                
                    return true;
                }
                return false;
            }
            
            template <bool InArray>
            static constexpr void True(std::istream & is, char & c)
            {
                Checked::consumeWhitespace(is, "completion of field value");
                int expectation[] = { 't', 'r', 'u', 'e' };
                for ( size_t i=0; i<4; i++ )
                    Checked::get(is, c, expectation[i], "completion of field value");

                Checked::consumeWhitespace(is, "\",\" or \"}\"");
                Checked::peek(is, c, "\",\" or \"}\"");
                if ( InArray && c != ',' && c != ']' )
                    throw Exception("Expected: \",\" or \"]\"");
                else if ( !InArray && c != ',' && c != '}' )
                    throw Exception("Expected: \",\" or \"}\"");
            }

            template <bool InArray>
            static constexpr void True(std::istream & is, char & c, std::stringstream & ss)
            {
                Consume::True<InArray>(is, c);
                ss << "true";
            }
            
            template <bool InArray>
            static constexpr void False(std::istream & is, char & c)
            {
                Checked::consumeWhitespace(is, "completion of field value");
                int expectation[] = { 'f', 'a', 'l', 's', 'e' };
                for ( size_t i=0; i<5; i++ )
                    Checked::get(is, c, expectation[i], "completion of field value");

                Checked::consumeWhitespace(is, "\",\" or \"}\"");
                Checked::peek(is, c, "\",\" or \"}\"");
                if ( InArray && c != ',' && c != ']' )
                    throw Exception("Expected: \",\" or \"]\"");
                else if ( !InArray && c != ',' && c != '}' )
                    throw Exception("Expected: \",\" or \"}\"");
            }

            template <bool InArray>
            static constexpr void False(std::istream & is, char & c, std::stringstream & ss)
            {
                Consume::False<InArray>(is, c);
                ss << "false";
            }

            template <bool InArray>
            static constexpr void Number(std::istream & is, char & c)
            {
                bool decimal = false;
                bool finished = false;
                Checked::get(is, c, "\"-\" or [0-9]");
                switch ( c )
                {
                    case '-': case '0': case '1': case '2': case '3': case '4':
                    case '5': case '6': case '7': case '8': case '9': break;
                    default: throw InvalidNumericCharacter(c, "\"-\" or [0-9]");
                }
                constexpr char terminator = InArray ? ']' : '}';
                do
                {
                    Checked::get<InArray>(is, c, "\",\" or \"]\"", "\",\" or \"}\"");

                    switch ( c )
                    {
                        case '.':
                            if ( decimal )
                                throw InvalidSecondDecimal();
                            else
                                decimal = true;
                            break;
                        case '0': case '1': case '2': case '3': case '4':
                        case '5': case '6': case '7': case '8': case '9':
                            break;
                        case ',': Checked::unget(is, ','); break;
                        case terminator: Checked::unget(is, terminator); break;
                        case ' ': case '\t': case '\n': case '\r':
                            Checked::consumeWhitespace<InArray>(is, decimal ? "[0-9], \",\", or \"]\"" : "\".\", [0-9], \",\", or \"]\"",
                                decimal ? "[0-9], \",\", or \"}\"" : "\".\", [0-9], \",\", or \"}\"");
                            Checked::get<InArray>(is, c, decimal ? "[0-9], \",\", or \"]\"" : "\".\", [0-9], \",\", or \"]\"",
                                decimal ? "[0-9], \",\", or \"}\"" : "\".\", [0-9], \",\", or \"}\"");

                            if ( InArray && c != ',' && c != ']' )
                                throw InvalidNumericCharacter(c, (decimal ? "[0-9], \",\", or \"]\"" : "\".\", [0-9], \",\", or \"]\""));
                            else if ( c != ',' && c != '}' )
                                throw InvalidNumericCharacter(c, (decimal ? "[0-9], \",\", or \"}\"" : "\".\", [0-9], \",\", or \"}\""));
                            else
                                Checked::unget(is, '\"');
                            break;
                        default:
                            throw InvalidNumericCharacter(c, (decimal ? "[0-9], \",\", or \"}\"" : "\".\", [0-9], \",\", or \"}\""));
                            break;
                    }
                }
                while ( c != ',' && c != terminator );
            }
            
            template <bool InArray>
            static constexpr void Number(std::istream & is, char & c, std::stringstream & ss)
            {
                bool decimal = false;
                bool finished = false;
                Checked::get(is, c, "\"-\" or [0-9]");
                switch ( c )
                {
                    case '-': case '0': case '1': case '2': case '3': case '4':
                    case '5': case '6': case '7': case '8': case '9': break;
                    default: throw InvalidNumericCharacter(c, "\"-\" or [0-9]");
                }
                ss.put(c);
                constexpr char terminator = InArray ? ']' : '}';
                do
                {
                    Checked::get<InArray>(is, c, "\",\" or \"]\"", "\",\" or \"}\"");
                    switch ( c )
                    {
                        case '.':
                            if ( decimal )
                                throw InvalidSecondDecimal();
                            else
                            {
                                decimal = true;
                                ss.put(c);
                            }
                            break;
                        case '0': case '1': case '2': case '3': case '4':
                        case '5': case '6': case '7': case '8': case '9':
                            ss.put(c);
                            break;
                        case ',': Checked::unget(is, ','); break;
                        case terminator: Checked::unget(is, terminator); break;
                        case ' ': case '\t': case '\n': case '\r':
                            Checked::consumeWhitespace<InArray>(is, decimal ? "[0-9], \",\", or \"]\"" : "\".\", [0-9], \",\", or \"]\"",
                                decimal ? "[0-9], \",\", or \"}\"" : "\".\", [0-9], \",\", or \"}\"");
                            Checked::get<InArray>(is, c, decimal ? "[0-9], \",\", or \"]\"" : "\".\", [0-9], \",\", or \"]\"",
                                decimal ? "[0-9], \",\", or \"}\"" : "\".\", [0-9], \",\", or \"}\"");

                            if ( InArray && c != ',' && c != ']' )
                                throw InvalidNumericCharacter(c, (decimal ? "[0-9], \",\", or \"]\"" : "\".\", [0-9], \",\", or \"]\""));
                            else if ( c != ',' && c != '}' )
                                throw InvalidNumericCharacter(c, (decimal ? "[0-9], \",\", or \"}\"" : "\".\", [0-9], \",\", or \"}\""));
                            else
                                Checked::unget(is, '\"');
                            break;
                        default:
                            throw InvalidNumericCharacter(c, (decimal ? "[0-9], \",\", or \"}\"" : "\".\", [0-9], \",\", or \"}\""));
                            break;
                    }
                }
                while ( c != ',' && c != terminator );
            }

            static void String(std::istream & is, char & c)
            {
                Checked::get(is, c, '\"', "string value open quote");
                do
                {
                    Checked::get(is, c, "string value close quote");
                    switch ( c )
                    {
                        case '\\': // Escape sequence
                            Checked::get(is, c, "completion of string escape sequence");
                            switch ( c )
                            {
                                case '\"': case '\\': case '/': case 'b': case 'f': case 'n': case 'r': case 't': break;
                                case 'u':
                                {
                                    char hexEscapeSequence[6] = { 'u', '\0', '\0', '\0', '\0', '\0' };
                                    for ( size_t i=1; i<5; i++ )
                                    {
                                        Checked::escapeSequenceGet(is, c, hexEscapeSequence);
                                        hexEscapeSequence[i] = c;
                                        if ( !((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f')) )
                                            throw InvalidEscapeSequence((std::string(hexEscapeSequence)).c_str(), unicodeEscapeSequence);
                                    }
                                }
                                break;
                            }
                            break;
                        case '\n': throw UnexpectedLineEnding("\\n");
                        case '\r': throw UnexpectedLineEnding("\\r");
                        case '\"': break; // Closing quote
                        default: break;
                    }
                } while ( c != '\"' );
            }

            static void String(std::istream & is, char & c, std::stringstream & ss)
            {
                Checked::get(is, c, '\"', "string value open quote");
                ss.put('\"');
                do
                {
                    Checked::get(is, c, "string value close quote");
                    ss.put(c);
                    switch ( c )
                    {
                        case '\\': // Escape sequence
                            Checked::get(is, c, "completion of string escape sequence");
                            switch ( c )
                            {
                                case '\"': break;
                                case '\\': break;
                                case '/': break;
                                case 'b': break;
                                case 'f': break;
                                case 'n': break;
                                case 'r': break;
                                case 't': break;
                                case 'u':
                                {
                                    char hexEscapeSequence[6] = { 'u', '\0', '\0', '\0', '\0', '\0' };
                                    for ( size_t i=1; i<5; i++ )
                                    {
                                        Checked::escapeSequenceGet(is, c, hexEscapeSequence);
                                        hexEscapeSequence[i] = c;
                                        if ( !((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f')) )
                                            throw InvalidEscapeSequence((std::string(hexEscapeSequence)).c_str(), unicodeEscapeSequence);
                                    }
                                }
                                break;
                            }
                            break;
                        case '\n': throw UnexpectedLineEnding("\\n");
                        case '\r': throw UnexpectedLineEnding("\\r");
                        case '\"': break; // Closing quote
                        default: break;
                    }
                } while ( c != '\"' );
            }
            
            template <typename Value>
            static constexpr void ConstPrimitive(std::istream & is)
            {
                typename std::remove_const<Value>::type placeholder;
                is >> placeholder;
            }

            template <bool InArray>
            static constexpr void Value(std::istream & is, char & c)
            {
                Checked::consumeWhitespace(is, "completion of field value");
                Checked::peek(is, c, "completion of field value");
                switch ( c )
                {
                    case '\"': Consume::String(is, c); break; // String or error
                    case '-': case '0': case '1': case '2': case '3': case '4': case '5':
                    case '6': case '7': case '8': case '9': Consume::Number<InArray>(is, c); break; // Number or error
                    case '{': Consume::Iterable<false>(is, c); break; // JSON object or error
                    case '[': Consume::Iterable<true>(is, c); break; // JSON array or error
                    case 't': Consume::True<InArray>(is, c); break; // "true" or error
                    case 'f': Consume::False<InArray>(is, c); break; // "false" or error
                    case 'n': Consume::Null<InArray>(is, c); break; // "null" or error
                    default: throw InvalidUnknownFieldValue(); break;
                }
            }
            
            template <bool InArray>
            static constexpr void Value(std::istream & is, char & c, std::stringstream & ss)
            {
                Checked::consumeWhitespace(is, "completion of field value");
                Checked::peek(is, c, "completion of field value");
                switch ( c )
                {
                    case '\"': Consume::String(is, c, ss); break; // String or error
                    case '-': case '0': case '1': case '2': case '3': case '4': case '5':
                    case '6': case '7': case '8': case '9': Consume::Number<InArray>(is, c, ss); break; // Number or error
                    case '{': Consume::Iterable<false>(is, c, ss); break; // JSON object or error
                    case '[': Consume::Iterable<true>(is, c, ss); break; // JSON array or error
                    case 't': Consume::True<InArray>(is, c, ss); break; // "true" or error
                    case 'f': Consume::False<InArray>(is, c, ss); break; // "false" or error
                    case 'n': Consume::Null<InArray>(is, c, ss); break; // "null" or error
                    default: throw InvalidUnknownFieldValue(); break;
                }
            }

            template <bool IsArray>
            static constexpr void Iterable(std::istream & is, char & c)
            {
                Checked::get<IsArray>(is, c, '[', '{', "array opening \"[\"", "object opening \"{\"");
                if ( !Checked::tryGet<IsArray>(is, ']', '}', "array closing \"]\" or array element", "object closing \"}\" or field name opening \"") )
                {
                    do
                    {
                        if constexpr ( !IsArray )
                        {
                            Consume::String(is, c);
                            Checked::get(is, c, ':', "field name-value separator \":\"");
                        }
                        Consume::Value<IsArray>(is, c);
                    }
                    while ( Checked::get<IsArray>(is, ',', ']', '}', "\",\" or array closing \"]\"", "\",\" or object closing \"}\"") );
                }
            }

            template <bool IsArray>
            static constexpr void Iterable(std::istream & is, char & c, std::stringstream & ss)
            {
                Checked::get<IsArray>(is, c, '[', '{', "array opening \"[\"", "object opening \"{\"");
                ss << (IsArray ? '[' : '{');
                if ( !Checked::tryGet<IsArray>(is, ']', '}', "array closing \"]\" or array element", "object closing \"}\" or field name opening \"") )
                {
                    bool isFirst = true;
                    do
                    {
                        if ( !isFirst )
                            ss << ',';
                        else
                            isFirst = false;

                        if constexpr ( !IsArray )
                        {
                            Consume::String(is, c, ss);
                            Checked::get(is, c, ':', "field name-value separator \":\"");
                            ss << ':';
                        }
                        Consume::Value<IsArray>(is, c, ss);
                    }
                    while ( Checked::get<IsArray>(is, ',', ']', '}', "\",\" or array closing \"]\"", "\",\" or object closing \"}\"") );
                }
                ss << (IsArray ? ']' : '}');
            }
        };

        namespace Read
        {
            inline namespace Affix
            {
                inline void ObjectPrefix(std::istream & is, char & c)
                {
                    Checked::get(is, c, '{', "object opening \"{\"");
                }

                inline bool TryObjectSuffix(std::istream & is)
                {
                    return Checked::tryGet(is, '}', "object closing \"}\" or field name opening \"");
                }

                inline bool FieldSeparator(std::istream & is)
                {
                    return Checked::get(is, ',', '}', "\",\" or object closing \"}\"");
                }

                inline void FieldNameValueSeparator(std::istream & is, char & c)
                {
                    Checked::get(is, c, ':', "field name-value separator \":\"");
                }

                template <bool IsObject>
                inline void IterablePrefix(std::istream & is, char & c)
                {
                    Checked::get<IsObject>(is, c, '{', '[', "object opening \"{\"", "array opening \"[\"");
                }

                template <bool IsObject>
                inline bool TryIterableSuffix(std::istream & is)
                {
                    return Checked::tryGet<IsObject>(is, '}', ']', "object closing \"}\" or field name opening \"", "array closing \"]\" or array element");
                }

                template <bool IsObject>
                inline bool IterableElementSeparator(std::istream & is)
                {
                    return Checked::get<IsObject>(is, ',', '}', ']', "\",\" or object closing \"}\"", "\",\" or array closing \"]\"");
                }
            }

            template <typename Object, typename Value, size_t FieldIndex, typename OpAnnotations, typename Field>
            static constexpr inline bool Customization(std::istream & is, Context & context, Object & obj, Value & value)
            {
                if constexpr ( is_specialized<Customize<Object, Value, FieldIndex, OpAnnotations, Field>>::value )
                    return Customize<Object, Value, FieldIndex, OpAnnotations, Field>::As(is, context, obj, value); // Customize fully specialized
                else if constexpr ( is_specialized<Customize<Object, Value, FieldIndex, OpAnnotations>>::value )
                    return Customize<Object, Value, FieldIndex, OpAnnotations>::As(is, context, obj, value); // Four Customize arguments specialized
                else if constexpr ( is_specialized<Customize<Object, Value, FieldIndex>>::value )
                    return Customize<Object, Value, FieldIndex>::As(is, context, obj, value); // Three Customize arguments specialized
                else if constexpr ( is_specialized<Customize<Object, Value>>::value )
                    return Customize<Object, Value>::As(is, context, obj, value); // Two Customize arguments specialized
                else if constexpr ( is_specialized<Customize<Object, Value, FieldIndex, Annotate<>, Field>>::value )
                    return Customize<Object, Value, FieldIndex, Annotate<>, Field>::As(is, context, obj, value); // Customize<5args>, OpAnnotations defaulted
                else if constexpr ( is_specialized<Customize<Object, Value, NoFieldIndex, OpAnnotations, Field>>::value )
                    return Customize<Object, Value, NoFieldIndex, OpAnnotations, Field>::As(is, context, obj, value); // Customize<5args>, FieldIndex defaulted
                else if constexpr ( is_specialized<Customize<Object, Value, NoFieldIndex, Annotate<>, Field>>::value )
                    return Customize<Object, Value, NoFieldIndex, Annotate<>, Field>::As(is, context, obj, value); // Customize<5args>, both defaulted
                else if constexpr ( is_specialized<Customize<Object, Value, NoFieldIndex, OpAnnotations>>::value )
                    return Customize<Object, Value, NoFieldIndex, OpAnnotations>::As(is, context, obj, value); // Customize<4args>, FieldIndex defaulted
                else if constexpr ( is_specialized<CustomizeType<Value, OpAnnotations, Field>>::value )
                    return CustomizeType<Value, OpAnnotations, Field>::As(is, context, value); // CustomizeType fully specialized
                else if constexpr ( is_specialized<CustomizeType<Value, OpAnnotations>>::value )
                    return CustomizeType<Value, OpAnnotations>::As(is, context, value); // CustomizeType<2args> specialized
                else if constexpr ( is_specialized<CustomizeType<Value>>::value )
                    return CustomizeType<Value>::As(is, context, value); // CustomizeType<1arg> specialized
                else if constexpr ( is_specialized<CustomizeType<Value, Annotate<>, Field>>::value )
                    return CustomizeType<Value, Annotate<>, Field>::As(is, context, value); // CustomizeType<3args>, OpAnnotations defaulted
                else
                    return false;
            }

            template <bool InArray, typename Value>
            static constexpr void Bool(std::istream & is, char & c, Value & value)
            {
                Checked::consumeWhitespace(is, "true or false");
                Checked::peek(is, c, "true or false");
                if ( c == 't' )
                {
                    Consume::True<InArray>(is, c);
                    if constexpr ( !std::is_const<Value>::value )
                        value = true;
                }
                else if ( c == 'f' )
                {
                    Consume::False<InArray>(is, c);
                    if constexpr ( !std::is_const<Value>::value )
                        value = false;
                }
                else
                    throw Exception("Expected: \"true\" or \"false\"");
            }

            static void String(std::istream & is, char & c, std::stringstream & ss)
            {
                Checked::get(is, c, '\"', "string value open quote");
                do
                {
                    Checked::get(is, c, "string value close quote");
                    switch ( c )
                    {
                        case '\\': // Escape sequence
                            Checked::get(is, c, "completion of string escape sequence");
                            switch ( c )
                            {
                                case '\"': ss.put('\"'); break;
                                case '\\': ss.put('\\'); break;
                                case '/': ss.put('/'); break;
                                case 'b': ss.put('\b'); break;
                                case 'f': ss.put('\f'); break;
                                case 'n': ss.put('\n'); break;
                                case 'r': ss.put('\r'); break;
                                case 't': ss.put('\t'); break;
                                case 'u':
                                {
                                    char hexEscapeSequence[6] = { 'u', '\0', '\0', '\0', '\0', '\0' };
                                    for ( size_t i=1; i<5; i++ )
                                    {
                                        Checked::escapeSequenceGet(is, c, hexEscapeSequence);
                                        hexEscapeSequence[i] = c;
                                        if ( !((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f')) )
                                            throw InvalidEscapeSequence((std::string(hexEscapeSequence)).c_str(), unicodeEscapeSequence);
                                    }
                                    for ( size_t i=1; i<5; i++ )
                                    {
                                        char & cRef = hexEscapeSequence[i];
                                        if ( cRef >= '0' && cRef <= '9' )
                                            hexEscapeSequence[i] -= '0';
                                        else if ( cRef >= 'A' && cRef <= 'F' )
                                            hexEscapeSequence[i] = cRef - 'A' + 10;
                                        else if ( cRef >= 'a' && cRef <= 'f' )
                                            hexEscapeSequence[i] = cRef - 'a' + 10;
                                    }
                                    uint8_t highCharacter = 0x10 * hexEscapeSequence[1] + hexEscapeSequence[2];
                                    uint8_t lowCharacter = 0x10 * hexEscapeSequence[3] + hexEscapeSequence[4];
                                    if ( highCharacter > 0 )
                                        ss.put(highCharacter);

                                    ss.put(lowCharacter);
                                }
                                break;
                            }
                            break;
                        case '\n': throw UnexpectedLineEnding("\\n");
                        case '\r': throw UnexpectedLineEnding("\\r");
                        case '\"': break; // Closing quote
                        default: ss.put(c); break;
                    }
                } while ( c != '\"' );
            }

            static void String(std::istream & is, char & c, std::string & str)
            {
                std::stringstream ss;
                Read::String(is, c, ss);
                str = ss.str();
            }

            template <typename T>
            static constexpr void String(std::istream & is, char & c, T & t)
            {
                std::stringstream ss;
                Read::String(is, c, ss);
                if constexpr ( !std::is_const<T>::value )
                    ss >> t;
            }
        
            static std::string String(std::istream & is, char & c)
            {
                std::string str;
                Read::String(is, c, str);
                return str;
            }
        
            static std::string String(std::istream & is)
            {
                char c = '\0';
                std::string str;
                Read::String(is, c, str);
                return str;
            }

            template <typename Field, typename Value>
            static constexpr void EnumInt(std::istream & is, Value & value)
            {
                using EnumType = typename promote_char<typename std::underlying_type<typename remove_pointer<Value>::type>::type>::type;
                typename std::remove_const<EnumType>::type temp;
                is >> temp;
                if constexpr ( !std::is_const<EnumType>::value )
                    value = (typename remove_pointer<Value>::type)temp;
            }
            
            template <bool InArray, typename Field, typename T, typename Object, bool AllowCustomization = true>
            static constexpr void Value(std::istream & is, Context & context, char & c, Object & object, T & value)
            {
                if constexpr ( AllowCustomization && Customizers::HaveSpecialization<Object, T, Field::Index, Annotate<>, Field> ) // Input for this is specialized
                {
                    std::stringstream ss;
                    Json::Consume::Value<InArray>(is, c, ss);
                    std::string preserved = ss.str();
                    if ( !Read::Customization<Object, T, Field::Index, Annotate<>, Field>(ss, context, object, value) )
                    {
                        std::stringstream subIs(preserved);
                        Read::Value<InArray, Field, T, Object, false>(subIs, context, c, object, value);
                    }
                    return;
                }

                if constexpr ( is_pointable<T>::value )
                {
                    using Dereferenced = typename remove_pointer<T>::type;
                    if constexpr ( std::is_base_of<Generic::Value, Dereferenced>::value )
                    {
                        if ( Consume::TryNull<InArray>(is, c) )
                        {
                            if ( !std::is_const<T>::value )
                                value = nullptr;
                        }
                        else if ( value == nullptr )
                        {
                            if ( !std::is_const<T>::value )
                            {
                                if constexpr ( std::is_same<std::shared_ptr<Dereferenced>, T>::value )
                                    value = std::shared_ptr<Dereferenced>(new Dereferenced());
                                else if constexpr ( std::is_same<std::unique_ptr<Dereferenced>, T>::value )
                                    value = std::unique_ptr<Dereferenced>(new Dereferenced());
                                else if constexpr ( std::is_same<Dereferenced*, T>::value )
                                    value = new Dereferenced();

                                Read::Value<InArray>(is, context, value);
                            }
                        }
                    }
                    else if ( value == nullptr ) // If value pointer is nullptr the only valid value is "null"
                    {
                        Consume::Null<InArray>(is, c);
                    }
                    else if constexpr ( is_pointable<Dereferenced>::value && !std::is_const<Dereferenced>::value )
                        Read::Value<InArray, Field>(is, context, c, object, *value);  // Only take the chance of assigning nullptr to that more deeply nested pointer
                    else if ( Consume::TryNull<InArray>(is, c) ) // If value pointer is not nullptr, "null" is a possible value
                    {
                        if constexpr ( !std::is_const<T>::value )
                            value = nullptr;
                    }
                    else
                        Read::Value<InArray, Field>(is, context, c, object, *value);
                }
                else if constexpr ( std::is_base_of<Generic::Value, T>::value )
                    ;
                else if constexpr ( is_iterable<T>::value )
                    Read::Iterable<Field, T>(is, context, c, object, value);
                else if constexpr ( Field::template HasAnnotation<IsRoot> )
                    Read::Object<T>(is, context, c, value);
                else if constexpr ( Field::template HasAnnotation<Reflect::Reflected> )
                    Read::Object(is, context, c, value);
                else if constexpr ( Field::template HasAnnotation<Json::String> )
                    Read::String(is, c, value);
                else if constexpr ( Field::template HasAnnotation<Json::EnumInt> )
                    Read::EnumInt<Field, T>(is, value);
                else if constexpr ( is_bool<T>::value )
                    Read::Bool<InArray>(is, c, value);
                else if constexpr ( std::is_const<T>::value )
                    Consume::ConstPrimitive<T>(is);
                else
                    is >> value;
            }

            template <bool InArray>
            static constexpr void Value(std::istream & is, Context & context, char & c, Generic::Value & value)
            {
                Checked::consumeWhitespace(is, "completion of field value");
                Checked::peek(is, c, "completion of field value");
                switch ( c )
                {
                    case '\"': // String or error
                        value.string() = Read::String(is, c);
                        break;
                    case '-': case '0': case '1': case '2': case '3': case '4': case '5':
                    case '6': case '7': case '8': case '9': // Number or error
                        Consume::Number<InArray>(is, c);
                        // TODO: Number reader
                        break;
                    case '{': // JSON object or error
                        Consume::Iterable<false>(is, c);
                        // TODO: Read generic object
                        break;
                    case '[': // JSON array or error
                        Consume::Iterable<true>(is, c);
                        // TODO: Read generic array
                        break;
                    case 't': // "true" or error
                        Consume::True<InArray>(is, c);
                        value.boolean() = true;
                        break;
                    case 'f': // "false" or error
                        Consume::False<InArray>(is, c);
                        value.boolean() = false;
                        break;
                    case 'n': // "null" or error
                        Consume::Null<InArray>(is, c);
                        throw Exception("Cannot place null in non-pointable value!"); // TODO: Specific exception
                        break;
                    default:
                        throw InvalidUnknownFieldValue();
                        break;
                }
            }

            template <bool InArray, typename Field, typename Key, typename T, typename Object>
            static constexpr void Value(std::istream & is, Context & context, char & c, Object & object, std::pair<Key, T> & pair)
            {
                Read::String(is, c, pair.first);
                Read::FieldNameValueSeparator(is, c);
                Read::Value<InArray, Field, T>(is, context, c, object, pair.second);
            }
            
            template <typename Field, typename T, typename Object>
            static constexpr void Iterable(std::istream & is, Context & context, char & c, Object & object, T & iterable)
            {
                using Element = typename element_type<T>::type;
                constexpr bool ContainsPairs = is_pair<Element>::value;

                Read::IterablePrefix<ContainsPairs>(is, c);
                if ( !Read::TryIterableSuffix<ContainsPairs>(is) )
                {
                    Clear(iterable);
                    size_t i=0;
                    do
                    {
                        if constexpr ( is_static_array<T>::value )
                        {
                            if ( i >= static_array_size<T>::value )
                                throw ArraySizeExceeded();
                            else
                                Read::Value<!ContainsPairs, Field>(is, context, c, object, iterable[i++]);
                        }
                        else // Appendable STL container
                        {
                            typename element_type<T>::type value;
                            Read::Value<!ContainsPairs, Field>(is, context, c, object, value);
                            Append<T, typename element_type<T>::type>(iterable, value);
                        }
                    }
                    while ( Read::IterableElementSeparator<ContainsPairs>(is) );
                }
            }

            static void Iterable(std::istream & is, Context & context, char & c, Generic::Value & value)
            {
                bool isObject = value.type() == Generic::Value::Type::Object;

                /*Read::IterablePrefix<ContainsPairs>(is, c);
                if ( !Read::TryIterableSuffix<ContainsPairs>(is) )
                {
                    Clear(iterable);
                    size_t i=0;
                    do
                    {
                        if constexpr ( is_static_array<T>::value )
                        {
                            if ( i >= static_array_size<T>::value )
                                throw ArraySizeExceeded();
                            else
                                Read::Value<!ContainsPairs, Field>(is, context, c, object, iterable[i++]);
                        }
                        else // Appendable STL container
                        {
                            typename element_type<T>::type value;
                            Read::Value<!ContainsPairs, Field>(is, context, c, object, value);
                            Append<T, typename element_type<T>::type>(iterable, value);
                        }
                    }
                    while ( Read::IterableElementSeparator<ContainsPairs>(is) );
                }*/
            }

            template <typename Object>
            static constexpr void Field(std::istream & is, Context & context, char & c, Object & object, const std::string & fieldName)
            {
                Read::FieldNameValueSeparator(is, c);
                JsonField* jsonField = getJsonField(object, fieldName);
                if ( jsonField != nullptr ) // Known field
                {
                    if ( jsonField->type == JsonField::Type::Regular )
                    {
                        Object::Class::FieldAt(object, jsonField->index, [&](auto & field, auto & value) {
                            using FieldType = typename std::remove_reference<decltype(field)>::type;
                            Read::Value<false, FieldType>(is, context, c, object, value);
                        });
                    }
                    else
                    {
                        Object::Supers::At(object, jsonField->index, [&](auto & superObj) {
                            using Super = typename std::remove_reference<decltype(superObj)>::type;
                            Read::Object<Super>(is, context, c, superObj);
                        });
                    }
                }
                else // Unknown field
                    Consume::Value<false>(is, c);
            }

            static inline std::string FieldName(std::istream & is, char & c)
            {
                std::string fieldName;
                try {
                    Read::String(is, c, fieldName);
                } catch ( UnexpectedLineEnding & e) {
                    throw FieldNameUnexpectedLineEnding(e);
                }
                return fieldName;
            }

            template <typename T>
            static constexpr void Object(std::istream & is, Context & context, char & c, T & t)
            {
                Read::ObjectPrefix(is, c);
                if ( !Read::TryObjectSuffix(is) )
                {
                    do
                    {
                        std::string fieldName = Read::FieldName(is, c);
                        Read::Field(is, context, c, t, fieldName);
                    }
                    while ( Read::FieldSeparator(is) );
                }
            }
        };
        
        template <typename T>
        class ReflectedObject
        {
        public:
            ReflectedObject(T & obj, std::shared_ptr<Context> context) : obj(obj), context(context) {}

            T & obj;
            std::shared_ptr<Context> context;

            std::istream & get(std::istream & is)
            {
                if ( context == nullptr )
                    context = std::shared_ptr<Context>(new Context());

                char c = '\0';
                Read::Value<false, ReflectedField<T>>(is, *context, c, obj, obj);
                return is;
            }
        };
        
        template <typename T>
        std::istream & operator>>(std::istream & is, Json::Input::ReflectedObject<T> object)
        {
            return object.get(is);
        }

        template <typename T>
        constexpr Input::ReflectedObject<T> in(T & t, std::shared_ptr<Context> context = nullptr)
        {
            return Input::ReflectedObject<T>(t, context);
        }
    }
    
};

#endif