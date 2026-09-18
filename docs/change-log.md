---------------------------------------------------
| Date         | Change             | Reason       |
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
  - Reason: AttendanceRecord needs to refer to an existing Student object rather than create a separate Student object.

- Represented `session : AttendanceSession` as `AttendanceSession* session`.
  - Reason: AttendanceRecord needs to refer to an existing AttendanceSession object rather than create or copy a separate session object.

- Added an AttendanceRecord constructor.
  - Reason: the UML does not specify a constructor or setter methods, but the private record attributes need to be initialized so that AttendanceRegister can create usable attendance records.

- Added `friend class AttendanceRegister`.
  - Reason: AttendanceRegister needs to access the private AttendanceRecord data when calculating student and course attendance percentages, without adding extra public methods that are not specified in the UML.


### CorrectionRecord – UML Deviations

- Changed `timestamp : time` from the UML to `time_t timestamp`.
  - Reason: `time` is not a standard usable C++ data type; `time_t` is the appropriate C++ type for storing a time value.

- Added a constructor to initialize the private attributes.
  - Reason: the UML does not specify a constructor or setter methods, so a constructor is required to create a usable CorrectionRecord.

- Kept `originalrecord : AttendanceRecord` and `actinglecuturer : Lecturer` as value members according to the UML.
  - Reason: `AttendanceRegister::addcorrections()` receives both the AttendanceRecord and Lecturer by value, and `Lecturer` is copyable in the existing Member 1 implementation.
  - Pointer members were considered but rejected because storing pointers to the by-value parameters would create dangling pointers after `addcorrections()` returns.

- ### AttendanceRegister – UML Deviations

- Changed `markpresent(Student student, AttendanceSession session)` to use
  `Student&` and `AttendanceSession&`.
  - Reason: AttendanceRecord stores pointers to the existing Student and
    AttendanceSession objects. Passing them by value would create pointers
    to temporary local copies that become invalid after `markpresent()`
    returns.

- Changed `getstudentpercentage(Student student, Course course)` to use
  `Student&` and `Course&`, and changed `getcoursepercentage(Course course)`
  to use `Course&`.
  - Reason: the methods need to compare the supplied objects with the
    existing Student and Course objects referenced by the attendance records.

- Added `friend class AttendanceRegister` to AttendanceRecord and
  AttendanceSession.
  - Reason: AttendanceRegister needs access to the private record and course
    relationship data required by the UML percentage methods.

- Attendance percentage calculation is based on the AttendanceRecord objects
  stored in the register.
  - Reason: the UML does not provide a separate collection of attendance
    sessions or a `markabsent()` operation.
  - No additional attendance methods or attributes were added.




