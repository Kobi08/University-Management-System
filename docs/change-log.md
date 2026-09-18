    --------------------------------------------------- 
    | Date         | Change          |  Reason        |   
    ---------------------------------------------------

1. ### TimeSlot
- Changed `operator==` return type from `ostream&` shown in the UML to `bool`.
  - Reason: equality/clash detection requires a boolean result.

- Added constructors and getter methods for TimeSlot.
  - Reason: required to create and access TimeSlot data from other classes.

### Timetable
- Implemented the UML `courses` relationship using `list<Course*>` instead of `list<Course>`.
  - Reason: `Course` is an abstract class and cannot be stored by value.

- Added `addCourse(Course&)`.
  - Reason: the UML contains a private course collection but provides no operation for adding courses to the timetable.
  - This is required to populate the timetable and perform clash detection.

### AttendanceSession
- Represented the UML `Course` relationship using `Course*`.
  - Reason: `Course` is abstract and cannot be stored directly as an object.

- `durationminute` defaults to `0`.
  - Reason: the UML does not provide a constructor parameter or setter for configuring the duration.

### RotatingCodeCapture – UML Deviation

- Added the private attribute `currentCode : string`.
  - The UML diagram does not explicitly show any attributes for `RotatingCodeCapture`.
  - This attribute was added because the attendance-code capture mechanism needs to store the currently generated attendance code during an active session.
  - No other attributes were added.






