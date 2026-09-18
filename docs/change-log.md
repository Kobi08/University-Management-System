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


### AttendanceRecord – UML Deviations

- Changed `timestamp : time` from the UML to `time_t timestamp`.
  - Reason: `time` is not a standard usable C++ data type; `time_t` is the appropriate C++ type for storing a time value.

- Represented `student : Student` as `Student* student`.
  - Reason: the existing Student class does not have a default constructor, and AttendanceRecord needs to refer to an existing Student rather than create a new Student object.

- Represented `session : AttendanceSession` as `AttendanceSession* session`.
  - Reason: AttendanceRecord needs to refer to an existing AttendanceSession rather than create or copy a separate session object.

- Added an AttendanceRecord constructor.
  - Reason: the UML does not specify a constructor or setter methods, but the private record attributes need to be initialized so that AttendanceRegister can create usable attendance records.

  ### CorrectionRecord – UML Deviations

- Changed `originalrecord : AttendanceRecord` to `AttendanceRecord* originalrecord`.
  - Reason: the correction record should refer to the existing AttendanceRecord rather than create a separate copy.

- Changed `actinglecuturer : Lecturer` to `Lecturer* actinglecuturer`.
  - Reason: the correction record should refer to the existing Lecturer rather than create a separate Lecturer object.

- Changed `timestamp : time` to `time_t timestamp`.
  - Reason: `time` is not a standard usable C++ data type; `time_t` is used to store the time value.

- Added a constructor to initialize the private attributes.
  - Reason: the UML does not specify a constructor or setter methods, so a constructor is required to create a usable CorrectionRecord.

- 




