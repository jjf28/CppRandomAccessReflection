# CppRandomAccessReflection
Creating a simpler, more intuitive means of C++ reflection




Within the class you're looking to reflect you place the REFLECT macro.

```
class FuelTank {
public:
    float capacity;
    float currentLevel;
    float tickMarks[2];

    REFLECT(FuelTank, (B) capacity, (B) currentLevel, (B) tickMarks)
};
```

The REFLECT macro takes the class name, then between 1 and 123 B or R fields or a mix of the two.

- B: Basic-type - a type which already has an acceptable representation when streamed
- R: Reflected-type - an object or object array which is also reflected

## Field
Information provided to REFLECT is used to generate meta-data about your classes fields in the form of "Field" objects stored in a sub-class of your object titled "Class", Field objects come in two flavors but both share the following members:

1. index
2. name
3. typeStr
4. arraySize (0 for fields that are not arrays)
5. isIterable (either an array or STL container)
6. containsPairs (STL maps always contain pairs, also true for any non-map iterables that have element type pair)
7. isReflected

## Class
As stated, Class is a sub-class of the class you're trying to reflect; Class has the following static data members:

1. totalFields
2. fields[totalFields] // Simple flavor, doesn't include the type or Lambda guards

Class also provides two static methods to retrieve information about fields
```
ForEachField(object, [&](auto field, auto value) {
	// Your code here
});
FieldAt(object, size_t fieldIndex, [&](auto field, auto value) {
	// Your code here
});
```

"value" is a reference to the actual field in the object, which you can read or change. "field" is the enhanced flavor of Field, meaning it includes the type (accessible using decltype(field)::type), as well as the "accelerators", which can be used to conviently use fields without hitting compiler errors.
```
field.ForPrimitive(value, [&](auto primitive) {
	// Your code here
});
field.ForObject(value, [&](auto object) {
	// Your code here
});
field.ForPrimitives(value, [&](auto index, auto primitive) { /* Your code here (excluded below) */ });
field.ForObjects(value, [&](auto index, auto object) { });
field.ForPrimitivePairs(value, [&](auto index, auto first, auto primitive) { });
field.ForObjectPairs(value, [&](auto index, auto first, auto object) { });

field.ForPrimitivePointers(value, [&](auto index, auto primitivePointer) { });
field.ForObjectPointers(value, [&](auto index, auto objectPointer) { });
field.ForPrimitivePointerPairs(value, [&](auto index, auto first, auto primitivePointer) { });
field.ForObjectPointerPairs(value, [&](auto index, auto first, auto objectPointer) { });
```

For the first six accelerators, if some of the fields may be nullpointer (e.g. you have a std::vector<int>* field) you're expected to use the null-check method first (as below), pointer fields are otherwise internally dereferenced by the first six accelerators to allow you to iterate their contents without needing to use a separate accelerator. If a field may contain pointers (e.g. std::vector<int*>) rather than being a pointer themselves, then you need to call one of the last four accelerators, pointers contained in arrays and STL containers will not automatically be dereferenced.

```
if ( field.IfNull(value) )
  // Code handling nullpointer
else
{
  field.ForPrimitives(value, [&](auto index, auto primitive) {
    // Code handling each primitive in some iterable field
  });
}
```

## Usage

Following the setup of the REFLECT macro, you can easily loop over the fields of a reflected class...

```
FuelTank::Class::ForEachField(fuelTank, [&](auto field, auto value) {
	std::cout << field.fieldName << ": " << value << std::endl;
});
```


Array access can be a little troublesome, e.g.:

```
FuelTank::Class::ForEachField(fuelTank, [&](auto field, auto value) {
	if ( field.isArray ) {
		std::cout << field.fieldName << ": " << value[0] << std::endl;
	}
});
```

Will cause a compiler error, as the compiler will attempt to generate array access of FuelTank::capacity and FuelTank::currentLevel in addition to the appropriate array access code for tickMarks.

Placing your array access code inside the appropriate guard method will circumvent the issue, e.g.
```
FuelTank::Class::ForEachField(fuelTank, [&](auto field, auto value) {
    field.IfPrimitive([&](auto) { std::cout << "(fuelTankPrimitive) " << field.fieldName << ": " << value << std::endl; });
    field.IfPrimitiveArray([&](auto) { std::cout << "(fuelTankPrimitiveArray) " << field.fieldName << ": " << value[0] << std::endl; });
});
```


Similarly attempting to access sub-object meta-data can run you into issues, e.g.:

```
template <typename T>
void TraverseFields(T & t)
{
	using Class = typename T::Class;
	Class::ForEachField(obj, [&](auto field, auto value) {
		TraverseFields<decltype(field)::type>(value);
	});
}
```

Will cause errors similar to the array access issue as the compiler attempts to create and use Class = T::Class on primitives (e.g. float::Class), you can guard against these just the same.

```
template <typename T>
void TraverseFields(T & t)
{
	using Class = typename T::Class;
	Class::ForEachField(obj, [&](auto field, auto value) {
		field.IfObject([&](auto) { TraverseFields<decltype(field)::type>(value); });
		field.IfObjectArray([&](auto) {
			for ( size_t i=0; i<field.arraySize; i++ ) {
				auto reflectedObject = value[i];
				TraverseFields<decltype(reflectedObject)>(reflectedObject);
			});
		}
	});
}
```

See [Json.h](https://github.com/jjf28/CppRandomAccessReflection/blob/master/CppRandomAccessReflection/Json.h) for a full traversal-and-print of all fields.

## How It Works

REFLECT is nothing more than a macro that defines the class Class, it does so using a concept called macro loops, macro loops start with static macro iterations...
```
#define FOR_EACH_1(f,a,...) f(a)
#define FOR_EACH_2(f,a,...) f(a) EXPAND(FOR_EACH_1(f,__VA_ARGS__))
#define FOR_EACH_3(f,a,...) f(a) EXPAND(FOR_EACH_2(f,__VA_ARGS__))
```
(could be longer)

f(a) simply calls the function-like macro "f", with the argument "a".
If you called FOR_EACH_3(f, a, b, c), it would be expanded to "f(a) f(b) f(c)"

With a count of the arguments we can concatenate FOR_EACH_ and the count to invoke the correct static macro iteration.

To count we lay out all of the arguments, appended with a list of all numbers from ArgMax to 0
```
a, b, c, 3, 2, 1, 0
         ^
```
And then select the argument at ArgMax, in this case 3, if we passed two arguments the layout would have been...
```
a, b, 3, 2, 1, 0
         ^
```
If we passed one argument...
```
a, 3, 2, 1, 0
         ^
```
With the count, and call to the appropriate static macro iteration, plus a little extra macro expansion and concatenation to avoid bugs with Visual Studios, we have all the magic needed to perform a FOR_EACH loop on a set of macro arguments.

The REFLECT macro takes in the name of the class you're adding reflection to, followed by a list of fields, in the form "B<type> fieldName", or "R<type> fieldName"; using the LHS and RHS macros to extract type and fieldName respectively and the for each macro we build the class "Class" one piece at a time...

1. totalFields gets set to the count of arguments, not including the class name
2. an enum "IndexOf" is generated using each field name, because enums start at 0 and count up, IndexOf::fieldName provides the index of a given field in a manner statically available at compile time (this especially helps us build switches later)
3. An alias for each type is defined (via "using") named the same as the fieldname
4. a subclass is defined for each field named fieldName_, in this subclass a typeStr and nameStr are constructed, and a "Field" object is defined, using the typeStr, nameStr, and a ton of methods from C++ type support https://en.cppreference.com/w/cpp/types , these Field objects are the enhanced flavor
5. a "Field" array is generated, similar to the field object defined in the third step, but the simple flavor
6. The ForEachField method is generated, calling the given function with the enhanced flavor of the Field and a reference to the field
7. The FieldAt method is generated, calling the given function with the enhanced flavor of the Field and a reference to the field at the given fieldIndex

See [Reflect.h](https://github.com/jjf28/CppRandomAccessReflection/blob/master/CppRandomAccessReflection/Reflect.h) for the full implementation of macro loops and the REFLECT macro.
