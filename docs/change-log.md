    --------------------------------------------------- 
    | Date         | Change          |  Reason        |   
    ---------------------------------------------------

1. 
***DATE***
## 2026-09-14

***CHANGE***
### TimeSlot
- Created `TimeSlot.h` based on the UML class diagram.
- Added default and parameterized constructors.
- Added getter methods for accessing TimeSlot attributes.
- Added `operator==` for comparing two TimeSlot objects.
- Kept `operator==` return type as `bool` 

***REASON***
Because an equality comparison must return a true/false result.
The UML diagram indicates `ostream&` as the return type for `operator==`; this was treated as a UML inconsistency and corrected in the C++ implementation.


2.

***DATE***

## 2026-09-15

***CHANGE***

### Person

- Made the Person constructor protected.

- Added const qualifiers to read-only member functions such as login(), getName(), and getId().

- Added a virtual destructor.

***REASON***

The constructor was made protected because Person is an abstract base class and should only be constructed through derived classes.

The const qualifiers ensure that read-only functions cannot modify the object.

The virtual destructor ensures proper destruction of derived objects through a Person base-class pointer.


3.






