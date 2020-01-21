AllocInFunc:

Initializing the smart pointer as an object inside the function allocates it as a function-
scope temporary in the stack. That's why it doesn't exist on function return. It should be 
initialized as a pointer because then it is allocated in the heap, outside of the function 
scope, and survives the function exit. Or, it could be returned as an object, when the 
calling function, by initializing the return object, will own it; but then, it could be 
copied on return (if the copy is not avoided by return value optimization).

https://stackoverflow.com/a/7181452/38234
"Once the reference is bound to an object, you can never reassign it. From that point 
forward, any time you use the reference, it's indistinguishable from using the object it 
refers to."
We assign the new value to the old address, not change the address to the (existant) new 
value. (Hence we copy the value?)

https://stackoverflow.com/a/3413547/38234
Move is applicable to CIAlgorithms::filterData.
In C++11, in addition to copy constructors, objects can have move constructors.
(And in addition to copy assignment operators, they have move assignment operators.)
The move constructor is used instead of the copy constructor, if the object has type 
"rvalue-reference" (Type&&).
std::move() is a cast that produces an rvalue - reference to an object, to enable moving 
from it.
It's a new C++ way to avoid copies. For example, using a move constructor, a std::vector 
could just copy its internal pointer to data to the new object, leaving the moved object in 
an incorrect state, avoiding to copy all data. This would be C++-valid.

ReturningRefs:

https://stackoverflow.com/questions/10080935/when-is-an-object-out-of-scope
https://stackoverflow.com/questions/752658/is-the-practice-of-returning-a-c-reference-variable-evil
https://en.wikipedia.org/wiki/Copy_elision#Return_value_optimization

https://www.dummies.com/programming/cpp/returning-a-reference-from-a-function-in-c/
Reference to a global variable can be returned. Or, if the function is a member function, 
a reference to a member variable can be returned. (Eli -- returns reference to global.)

References to member variables could be returned, but raises the flow problem. Instead,
smart pointers, or return objects.

https://stackoverflow.com/a/7571379/38234:
Object is identified by address. At another address, you have to construct a new one; 
objects can't be moved. (Even with C++11, the new “move” semantics don't actually move an 
object; they provide an optimized way of moving its value, if you know that you won't need 
the value from where you're moving it.)