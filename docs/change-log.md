---------------------------------------------------
| Date         | Change             | Reason       |
---------------------------------------------------
## 2026-09-19

### TimeSlot

- Changed `operator==` return type from `ostream&` shown in the UML to `bool`.
- Added constructors for `TimeSlot`.
- Added getter methods for `TimeSlot`.

### Reason

The `operator==` function is used for equality and timetable clash detection, so a boolean return value is required.

The constructors and getter methods are required to create and access `TimeSlot` data from other classes.

### UML / Code Deviations

1. Changed `operator==` return type from `ostream&` to `bool`.
2. Added constructors for `TimeSlot`.
3. Added getter methods for `TimeSlot`.

These changes are limited to the implementation requirements and do not introduce additional domain responsibilities.


## 2026-09-19

### Timetable

- Implemented the UML `courses` relationship using `list<Course*>` instead of `list<Course>`.
- Added `addCourse(Course&)`.
- Implemented timetable display and course clash detection using the associated Course TimeSlots.

### Reason

`Course` is an abstract class and cannot be stored by value. `Course*` allows the Timetable to refer to existing Course objects.

The UML contains a private course collection but does not provide an operation for adding courses to the timetable. `addCourse()` is therefore required to populate the timetable and perform clash detection.

### UML / Code Deviations

1. `courses` changed from `list<Course>` to `list<Course*>`.
2. Added `addCourse(Course&)`.

These changes preserve the intended Course-Timetable relationship while using a valid C++ representation for an abstract Course type.


## 2026-09-19

### AttendanceSession

- Represented the UML `Course` relationship using `Course*`.
- Initialized `durationminute` to `0`.
- Implemented session opening, closing, expiry checking, and attendance-capture method assignment.
- Added move construction and move assignment while keeping copy assignment disabled.

### Reason

`Course` is an abstract class and cannot be stored directly as an object, so a pointer is used to refer to the associated Course.

The UML does not provide a constructor parameter or setter for configuring `durationminute`, so it is initialized to `0`.

The session operations are implemented according to the responsibilities represented by the UML and the `AttendanceCapture` relationship.

### UML / Code Deviations

1. Represented the UML `Course` relationship using `Course*`.
2. `durationminute` defaults to `0`.
3. Move operations and deleted copy assignment are implementation-level lifecycle handling required by the current class design.

No additional public domain operations were introduced.


## 2026-09-19

### AttendanceCapture

- Implemented `AttendanceCapture` as an abstract interface with the UML-specified capture operations.
- No `AttendanceCapture.cpp` file was created.

### Reason

`beginSession()`, `captureNext()`, and `endSession()` are pure virtual functions and therefore do not have concrete implementations in the abstract interface.

### UML / Code Deviations

1. No `.cpp` implementation file was added because the class contains only pure virtual operations.
2. No additional public methods or attributes were added.


## 2026-09-19

### RotatingCodeCapture

- Implemented `RotatingCodeCapture` as a derived class of `AttendanceCapture`.
- Implemented `beginSession()`, `captureNext()`, and `endSession()`.
- Added the private `currentCode : string` attribute to store the generated attendance code.

### Reason

The class implements the `AttendanceCapture` interface and provides attendance-code capture behaviour.

`currentCode` is required to store the currently generated attendance code during an active attendance session because the UML does not explicitly show attributes for `RotatingCodeCapture`.

No additional rotation interval, timer, or code-generation attributes were added because these are not specified in the UML.

### UML / Code Deviations

1. Added the private `currentCode : string` attribute.
2. No constructor was added because the UML does not specify one.
3. No additional rotation interval, timer, or code-generation attributes were added.

These changes keep the implementation within the intended responsibilities of `RotatingCodeCapture`.


## 2026-09-19

### AttendanceRecord

- Implemented the `AttendanceRecord` attributes and stream output operation.
- Changed `timestamp : time` from the UML to `time_t timestamp`.
- Represented `student : Student` as `Student* student`.
- Represented `session : AttendanceSession` as `AttendanceSession* session`.
- Added an `AttendanceRecord` constructor.
- Added `friend class AttendanceRegister`.

### Reason

`time` is not a standard usable C++ data type for storing a time value, so `time_t` is used.

`AttendanceRecord` needs to refer to the existing Student and AttendanceSession objects rather than create separate copies, so pointers are used.

The constructor is required to initialize the private record attributes because the UML does not specify setter methods.

`AttendanceRegister` requires access to the private record information when performing the UML-specified attendance calculations. Friend access avoids adding additional public methods that are not specified in the UML.

### UML / Code Deviations

1. `timestamp : time` → `time_t timestamp`.
2. `student : Student` → `Student* student`.
3. `session : AttendanceSession` → `AttendanceSession* session`.
4. Added an `AttendanceRecord` constructor.
5. Added `friend class AttendanceRegister`.

No additional public methods or attributes were added.


## 2026-09-19

### CorrectionRecord

- Implemented the `CorrectionRecord` attributes according to the UML.
- Changed `timestamp : time` from the UML to `time_t timestamp`.
- Added a constructor to initialize the private attributes.
- Kept `originalrecord : AttendanceRecord` as a value member.
- Kept `actinglecuturer : Lecturer` as a value member.

### Reason

`time` is not a standard usable C++ data type for storing a time value, so `time_t` is used.

The constructor is required to initialize the private attributes because the UML does not specify setter methods.

The UML specifies `AttendanceRecord` and `Lecturer` as value attributes. The existing `Lecturer` class is copyable, so these value members can be represented directly.

Pointer members were considered but not retained because `AttendanceRegister::addcorrections()` receives the AttendanceRecord and Lecturer by value, and storing pointers to those local parameters would create dangling pointers after the function returns.

### UML / Code Deviations

1. `timestamp : time` → `time_t timestamp`.
2. Added a constructor to initialize the private attributes.

`originalrecord` and `actinglecuturer` remain value members as specified by the UML.


## 2026-09-19

### AttendanceRegister

- Implemented the UML `records : list<AttendanceRecord>` relationship.
- Implemented the UML `corrections : list<CorrectionRecord>` relationship.
- Implemented `markpresent()`.
- Implemented `addcorrections()`.
- Implemented `getstudentpercentage()`.
- Implemented `getcoursepercentage()`.

### Reason

The `records` and `corrections` collections are implemented as value lists, matching the UML.

`markpresent()` creates an AttendanceRecord for the supplied Student and AttendanceSession.

`addcorrections()` creates and stores a CorrectionRecord containing the original attendance record, reason, lecturer, and correction timestamp.

The percentage functions inspect the stored attendance records and use the associated Student, AttendanceSession, Course, and status information to calculate attendance percentages.

Friend access allows the register to use the required private data without introducing additional public getters that are not specified in the UML.

### UML / Code Deviations

1. `markpresent(Student student, AttendanceSession session)` uses `Student&` and `AttendanceSession&` in the implementation.
2. The percentage method parameters use references where necessary to identify the existing Student and Course objects.
3. Added `friend class AttendanceRegister` to `AttendanceRecord` and `AttendanceSession`.
4. No additional public attributes or domain methods were added.

The reference changes prevent pointers stored by `AttendanceRecord` from referring to temporary local copies created by pass-by-value parameters.


## 2026-09-19

### CMake Build Configuration

- Added `src/AttendanceRegister.cpp` to the `UniversityManagementSystem` executable source list.

### Reason

`AttendanceRegister.cpp` must be included in the CMake target so that the AttendanceRegister implementation is compiled and linked when the project is built with CMake.

### UML / Code Deviations

1. Updated the build configuration only; no UML class, attribute, relationship, or domain method was changed.