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
**\*\****\*DATE\****\*\***

**## 2026-09-15**

**\*\****\*CHANGE\****\*\***

**### Course - TimeSlot**

- Changed the `Course` class `timeslot` attribute from `list<Timetable*>` to `list<TimeSlot>`.
- Added `TimeSlot.h` to `Course.h`.
- Changed the attribute name from `timeslot` to `timeslots` to represent that a course can have one or more weekly TimeSlots.
- Implemented the Course-TimeSlot relationship as composition by storing `TimeSlot` objects directly inside `Course`.

**\*\****\*REASON\****\*\***

The UML diagram shows `Course` and `TimeSlot` as a composition relationship, meaning that the `Course` owns its associated TimeSlot objects.

The original UML attribute was written as `list<Timetable>`, while the actual class representing an individual scheduled time is `TimeSlot`. Therefore, `list<TimeSlot>` correctly represents the intended Course-TimeSlot composition in the C++ implementation.

The `Course-Timetable` aggregation relationship is kept separately, with `Timetable` managing references to courses rather than being used as the Course's TimeSlot collection.








