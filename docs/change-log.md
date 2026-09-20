# CO2203 OOP Group Project
## Design Change Log

This document records design and implementation changes made after the approved design checkpoint. Each entry describes the affected component, the implemented change, the reason for the change, and any relevant UML/code deviation.

---

# 2026-09-18

## Person

### Changes
- Made the `Person` constructor `protected`.
- Added `const` qualifiers to read-only functions such as `login()`, `getName()`, and `getId()`.
- Added a `virtual` destructor.
- Added a private static `generateId()` helper.
- Implemented automatic ID generation using the `U001`, `U002`, `U003`, ... format.

### Reason
- The protected constructor prevents direct construction of the abstract `Person` class.
- `const` functions prevent read-only operations from modifying the object.
- The virtual destructor supports safe destruction of derived objects through a `Person` pointer.
- `generateId()` keeps ID-generation logic inside the `Person` class.

### UML / Code Deviations
1. `Person` constructor visibility changed to `protected`.
2. `const` qualifiers were added to read-only functions.
3. A virtual destructor was added.
4. A private `generateId()` helper was added.
5. UML uses `getname()`, `getid()`, and `showmenu()`, while the code uses `getName()`, `getId()`, and `showMenu()`.

---

## Student

### Changes
- Changed `enrollCourse(Course c)` to `enrollCourse(Course& course)`.
- Changed `dropCourse(Course c)` to `dropCourse(Course& course)`.
- Changed `isEnrolled(Course c)` to `isEnrolled(const Course& course) const`.
- Added `const` qualifiers to `hasCompleted()` and `viewTimetable()`.
- Added `~Student() override = default`.

### Reason
`Course` is an abstract class, so passing it by value is inappropriate because it can cause object slicing. References allow the original `Course` object to be used without copying or slicing.

The `const` qualifiers were added to read-only functions to prevent them from modifying the `Student` object.

The virtual default destructor explicitly overrides the virtual destructor inherited from `Person` and supports safe destruction through the inheritance hierarchy.

---

## Lecturer

### Changes
- Changed `viewEnrolment(Course)` to `viewEnrolment(Course& course) const`.
- Changed `openAttendanceSession(TimeSlot)` to `openAttendanceSession(const TimeSlot& slot)`.
- Added `~Lecturer() override = default`.

### Reason
References avoid unnecessary copying of domain objects, while `const` ensures that read-only operations do not modify the Lecturer.

The virtual destructor supports safe destruction of Lecturer objects through the polymorphic `Person` base class.

### UML / Code Deviations
1. `viewEnrolment()` uses `Course&` and `const` instead of passing `Course` by value.
2. `openAttendanceSession()` uses `const TimeSlot&` instead of passing `TimeSlot` by value.
3. A virtual destructor override was added.

---

## Administrator

### Changes
- Changed `createCourse()` and `editCourse()` lecturer parameters from `Lecturer` to `Lecturer&`.
- Added `const` references for string and prerequisite-list parameters.
- Changed `removeUser()` to return `bool`.
- Changed `removeCourse()` to return `string`.
- Added `~Administrator() override = default`.

### Reason
References avoid unnecessary copying of existing Lecturer objects. `const` references avoid unnecessary copying while preventing modification of supplied arguments.

The return values of `removeUser()` and `removeCourse()` allow the result of the operation to be reported.

The virtual destructor safely overrides the `Person` destructor.

---

## Course – TimeSlot

### Changes
- Changed the `Course` `timeslot` attribute from `list<Timetable>` to `list<TimeSlot>`.
- Added `TimeSlot.h` to `Course.h`.
- Implemented the Course–TimeSlot relationship by storing `TimeSlot` objects directly inside `Course`.

### Reason
The design identifies the Course–TimeSlot relationship as composition.

`TimeSlot` represents an individual scheduled time, so `list<TimeSlot>` directly represents the relationship.

The Course–Timetable aggregation remains separate, with `Timetable` managing references to courses.

---

## AssessmentMarks and Course Grading Interface

### Changes
- Added the `AssessmentMarks` class.
- Added `caScore`, `examScore`, `practicalMarks`, and `submissionScore`.
- Added a constructor and getter/setter methods.
- Initialized CA, examination, and submission scores to `-1`.
- Initialized practical marks as an empty list.
- Added validation for marks between 0 and 100.
- Added `invalid_argument` exceptions for invalid marks.
- Changed `Course::calculategrade()` to `calculategrade(const AssessmentMarks& marks)`.
- Associated `AssessmentMarks` with `Enrolment`.

### Reason
Assessment marks are specific to individual students and should not be shared by every student taking a Course.

A separate `AssessmentMarks` class therefore stores student-specific assessment information.

`-1` represents a mark that has not yet been entered, while valid marks are restricted to 0–100.

The grading interface receives `AssessmentMarks` so that each Course subclass can calculate grades using the relevant student's marks while retaining runtime polymorphism.

---

## Course Relationships, Functions and Object Lifecycle

### Changes
- Changed `enroledstudentdetails` from `list<Enrolment>` to `list<Enrolment*>`.
- Changed `asignlecturer` from `Lecturer` to `Lecturer*`.
- Changed `viewenrolment()` to return `list<Enrolment*>`.
- Added `addTimeSlot(const TimeSlot& slot)`.
- Added `getTimeSlots()`.
- Added `addEnrolment(Enrolment& enrolment)`.
- Added a `Course` constructor.
- Added a virtual destructor.

### Reason
The Course maintains references to existing Enrolment and Lecturer objects rather than storing separate copies.

The additional methods provide controlled access to TimeSlots and enrolments.

The constructor initializes Course information including capacity, Lecturer, and prerequisites.

The virtual destructor supports safe destruction of derived Course objects through the base Course class.

---

## LectureCourse

### Changes
- Implemented `LectureCourse` as a public derived class of `Course`.
- Added a constructor.
- Implemented `calculategrade(const AssessmentMarks& marks)`.
- Added validation for missing CA and examination marks.
- Implemented a project-defined 40% CA / 60% final examination weighting.

### Reason
`LectureCourse` provides specialized grading behaviour while following the Course hierarchy and supporting runtime polymorphism.

Assessment marks remain in `AssessmentMarks` because they belong to individual students.

The 40% / 60% weighting is a project-defined implementation assumption and is not presented as an official university grading rule.

---

## LabCourse

### Changes
- Removed `practicalmarks : list<double>` from `LabCourse`.
- Added a `LabCourse` constructor.
- Implemented `calculategrade(const AssessmentMarks& marks)`.
- Added validation for missing practical marks.
- Implemented grading using the average of entered practical marks.

### Reason
Practical marks are student-specific and therefore belong in `AssessmentMarks`.

The average-of-practical-marks calculation is a project-defined implementation assumption.

---

## ProjectCourse

### Changes
- Removed `submissionscore : double` from `ProjectCourse`.
- Added a `ProjectCourse` constructor.
- Implemented `calculategrade(const AssessmentMarks& marks)`.
- Added validation for missing submission scores.
- Used the student's submission score as the ProjectCourse grade.

### Reason
Submission scores are specific to individual students and are therefore stored in `AssessmentMarks`.

Using the submission score directly as the ProjectCourse grade is a project-defined implementation assumption because the project specification does not provide a specific ProjectCourse grading formula.

---

## Enrolment

### Changes
- Changed `student` from `Student` to `Student*`.
- Changed `course` from `Course` to `Course*`.
- Changed `dateEnrolled` from `date` to `string`.
- Added `AssessmentMarks* assessmentMarks`.
- Added `setAssessmentMarks(AssessmentMarks& marks)`.
- Added `calculateGrade()`.
- Added `getStudent() const`.
- Added `getCourse() const`.
- Added a friend `operator<<`.

### Reason
Pointers allow Enrolment to refer to existing Student and Course objects instead of creating copies.

`dateEnrolled` is currently represented as a string to avoid introducing an additional date class.

`AssessmentMarks` stores student-specific assessment information associated with the Enrolment.

---

## Custom Exception Hierarchy

### Changes
- Created `Exception` derived from `std::runtime_error`.
- Added `CourseFullException`.
- Added `PrerequisiteNotMetException`.
- Added `TimetableClashException`.

### Reason
The project requires a custom exception hierarchy for domain-level rule violations.

These exception types allow different enrolment validation failures to be identified and handled separately.

---

# 2026-09-19

## TimeSlot

### Changes
- Changed `operator==` to return `bool`.
- Added constructors.
- Added getter methods.

### Reason
`operator==` is used for equality and timetable clash detection, so a boolean return value is required.

Constructors and getters are required to create and access TimeSlot data.

### UML / Code Deviations
1. Changed `operator==` return type from `ostream&` shown in the UML to `bool`.
2. Added constructors for `TimeSlot`.
3. Added getter methods for `TimeSlot`.

---

## Timetable

### Changes
- Implemented the UML `courses` relationship using `list<Course*>`.
- Added `addCourse(Course&)`.
- Added `removeCourse(Course&)`.
- Implemented timetable display and course clash detection using Course TimeSlots.

### Reason
`Course` is abstract and therefore cannot be stored by value in the timetable.

Pointers allow the Timetable to refer to existing Course objects.

The additional operations are required to manage courses in the timetable and perform clash detection.

### UML / Code Deviations
1. `courses` changed from `list<Course>` to `list<Course*>`.
2. Added `addCourse(Course&)`.
3. Added `removeCourse(Course&)`.

---

## AttendanceSession

### Changes
- Represented the Course relationship using `Course*`.
- Initialized `durationminute` to `0`.
- Implemented session opening, closing, expiry checking, and attendance-capture assignment.
- Added move construction and move assignment while keeping copy assignment disabled.

### Reason
Course is abstract and cannot be stored directly as an object, so a pointer is used to refer to the associated Course.

The session operations implement the responsibilities represented in the UML.

Move operations and disabled copy assignment provide lifecycle handling required by the current implementation.

### UML / Code Deviations
1. Represented the UML Course relationship using `Course*`.
2. `durationminute` defaults to `0`.
3. Move operations and deleted copy assignment were added for implementation-level lifecycle handling.

---

## AttendanceCapture

### Changes
- Implemented `AttendanceCapture` as an abstract interface.
- Implemented the UML-specified capture operations as pure virtual functions.
- No `.cpp` file was created.

### Reason
`beginSession()`, `captureNext()`, and `endSession()` are pure virtual functions and therefore do not require concrete implementations in the abstract interface.

### UML / Code Deviations
1. No `.cpp` implementation file was added because the class contains only pure virtual operations.
2. No additional public methods or attributes were added.

---

## RotatingCodeCapture

### Changes
- Implemented `RotatingCodeCapture` as a derived class of `AttendanceCapture`.
- Implemented `beginSession()`, `captureNext()`, and `endSession()`.
- Added private `currentCode : string`.

### Reason
`currentCode` stores the currently generated attendance code during an active session.

No additional rotation interval, timer, or code-generation attributes were added because they were not specified in the UML.

### UML / Code Deviations
1. Added the private `currentCode : string` attribute.
2. No constructor was added because the UML does not specify one.
3. No additional rotation interval, timer, or code-generation attributes were added.

---

## RotatingCodeCapture Integration

### Changes
- Updated `captureNext()` to validate the entered attendance code against the current active session code.
- A matching code is returned.
- Invalid input returns an empty string.

### Reason
Validation was implemented inside `captureNext()` without introducing a separate public validation method, keeping the existing interface unchanged.

### UML / Code Deviations
1. No new public validation method was added.
2. `captureNext()` now validates the captured code against the private `currentCode`.
3. Invalid input returns an empty string.

---

## AttendanceRecord

### Changes
- Implemented the AttendanceRecord attributes and stream output.
- Changed `timestamp : time` to `time_t timestamp`.
- Changed `student : Student` to `Student* student`.
- Changed `session : AttendanceSession` to `AttendanceSession* session`.
- Added an AttendanceRecord constructor.
- Added `friend class AttendanceRegister`.

### Reason
`time_t` provides a usable C++ representation for time values.

Pointers allow AttendanceRecord to refer to existing Student and AttendanceSession objects.

The constructor initializes the private record attributes.

Friend access allows AttendanceRegister to use the required private information without adding unnecessary public methods.

### UML / Code Deviations
1. `timestamp : time` → `time_t timestamp`.
2. `student : Student` → `Student* student`.
3. `session : AttendanceSession` → `AttendanceSession* session`.
4. Added an AttendanceRecord constructor.
5. Added `friend class AttendanceRegister`.

---

## CorrectionRecord

### Changes
- Implemented the CorrectionRecord attributes.
- Changed `timestamp : time` to `time_t timestamp`.
- Added a constructor.

### Reason
`time_t` is used as the C++ representation of a time value.

The constructor initializes private attributes because the UML does not specify setter methods.

`AttendanceRecord` and `Lecturer` remain value members as represented in the UML.

### UML / Code Deviations
1. `timestamp : time` → `time_t timestamp`.
2. Added a constructor to initialize the private attributes.

---

## AttendanceRegister

### Changes
- Implemented `records : list<AttendanceRecord>`.
- Implemented `corrections : list<CorrectionRecord>`.
- Implemented `markpresent()`.
- Implemented `addcorrections()`.
- Implemented `getstudentpercentage()`.
- Implemented `getcoursepercentage()`.

### Reason
The collections match the UML relationships.

`markpresent()` creates attendance records after validation.

`addcorrections()` stores correction information for attendance changes.

The percentage functions calculate attendance using the stored attendance records.

### UML / Code Deviations
1. `markpresent(Student student, AttendanceSession session)` uses `Student&` and `AttendanceSession&` in the implementation.
2. Percentage method parameters use references where necessary to identify existing Student and Course objects.
3. Added friend access where required by the attendance implementation.
4. No additional public attributes or domain methods were added.

---

## CMake Build Configuration

### Changes
- Added `src/AttendanceRegister.cpp` to the `UniversityManagementSystem` executable source list.

### Reason
`AttendanceRegister.cpp` must be included in the CMake target so that the AttendanceRegister implementation is compiled and linked.

### UML / Code Deviations
- No UML class, attribute, relationship, or domain method was changed.

---

## Member 1 ↔ Member 2 Integration

### Changes

#### Exception Hierarchy
- Added `NotEnrolledException`.
- Added `DuplicateAttendanceException`.
- Added `SessionClosedException`.

These exceptions extend the existing `Exception` base class and provide the required attendance-related exception types.

#### AttendanceSession Integration
- Added `AttendanceSession(Course&, const TimeSlot&, int durationminute)`.
- Added `isOpen() const`.
- Added `getCourse() const`.
- Added `getTimeSlot() const`.
- Added `getDurationMinute() const`.

#### Course Integration
- Added `getLecturer() const`.

#### Lecturer Integration
- Added `AttendanceSession* activeSession`.
- Added `addCourse(Course&)`.
- Changed `openAttendanceSession()` to accept a duration.
- Added `getActiveSession() const`.
- Connected Lecturer, Course, TimeSlot, and AttendanceSession.

#### AttendanceRegister Integration
- Added session-open validation using `SessionClosedException`.
- Added student-enrolment validation using `NotEnrolledException`.
- Added duplicate-attendance validation using `DuplicateAttendanceException`.
- Attendance records are created only after the required validation checks succeed.
- Connected AttendanceRegister with the existing Enrolment interface.

### Reason
These changes connect the Member 1 domain model with the Member 2 attendance implementation.

The additional interfaces allow the existing UML classes and relationships to work together without introducing new domain classes.

`activeSession` is required because the Lecturer needs to retain the currently active session for attendance operations and closing.

The duration parameter allows the session duration to be supplied when an attendance session is opened.

### UML / Code Deviations
1. Added `NotEnrolledException`.
2. Added `DuplicateAttendanceException`.
3. Added `SessionClosedException`.
4. Added the parameterized AttendanceSession constructor.
5. Added AttendanceSession accessors.
6. Added `Course::getLecturer() const`.
7. Added `Lecturer::addCourse(Course&)`.
8. Added private `Lecturer::activeSession`.
9. Changed `openAttendanceSession()` to accept a duration.
10. Added `Lecturer::getActiveSession() const`.

These changes provide the implementation interface required to connect the Member 1 and Member 2 components.

---

# 2026-09-20

## AttendanceSession Lifetime Integration

### Changes
- Updated Lecturer to retain closed `AttendanceSession` objects until the Lecturer is destroyed.
- Added private `sessionHistory : list<AttendanceSession*>`.
- Changed `closeAttendanceSession()` so that it closes the session without immediately deleting it.
- Retained previous sessions when replacing an active session.
- Added cleanup of retained sessions in the Lecturer destructor.

### Reason
`AttendanceRecord` stores a pointer to its associated `AttendanceSession`.

Immediately deleting a closed session would leave existing AttendanceRecord objects with dangling `AttendanceSession*` pointers.

Closed sessions are therefore retained until the Lecturer is destroyed. This preserves the lifetime required by existing attendance records while allowing the Lecturer destructor to clean them up.

### UML / Code Deviations
1. Added private `sessionHistory : list<AttendanceSession*>`.

This is an implementation-level ownership addition required to preserve the lifetime of AttendanceSession objects referenced by AttendanceRecord.

---

## AttendanceRegister — Session Expiry Validation

### Changes
- Added an expiry check to `AttendanceRegister::markpresent()`.
- Attendance is rejected when the associated AttendanceSession has expired.
- `SessionClosedException` is thrown when an expired session is used to mark attendance.

### Reason
`AttendanceSession` already provides the `isExpired()` operation.

The AttendanceRegister must prevent attendance from being recorded after the attendance session has expired.

### UML / Code Deviations
- No UML deviation was introduced.

The implementation uses the existing `AttendanceSession::isExpired()` operation to validate whether attendance can be recorded.

---

# Note

Member 3 persistence and UI changes will be added after the final Member 3 implementation is reviewed and integrated. The final changelog should be updated again before submission to include only verified changes present in the final integrated code.