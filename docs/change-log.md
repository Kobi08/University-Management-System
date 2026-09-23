# CO2203 OOP Group Project

## Design Change Log

This document records design and implementation changes made after the approved design checkpoint. Each entry describes the affected component, the implemented change, the reason for the change, and relevant UML/code deviations.

---

# 2026-09-18

## Person

### Changes

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

1. `viewEnrolment()` uses `Course&` and `const` instead of passing `Course` by value.
2. `openAttendanceSession()` uses `const TimeSlot&` instead of passing `TimeSlot` by value.
3. A virtual destructor override was added.

---

## Administrator

### Changes

### Changes
- Changed `createCourse()` and `editCourse()` lecturer parameters from `Lecturer` to `Lecturer&`.
- Added `const` references for string and prerequisite-list parameters.
- Changed `removeUser()` to return `bool`.
- Changed `removeCourse()` to return `string`.
- Added `~Administrator() override = default`.

### Reason
References avoid unnecessary copying of existing Lecturer objects. `const` references avoid unnecessary copying while preventing modification of supplied arguments.

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
- Added constructor and getter/setter methods.
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
Pointers allow Enrolment to refer to existing Student and Course objects instead of creating copies.

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

Move operations and disabled copy operations provide lifecycle handling required by the current implementation.

### UML / Code Deviations

1. Represented the UML Course relationship using `Course*`.
2. `durationminute` defaults to `0`.
3. Move operations and deleted copy operations were added for implementation-level lifecycle handling.

---

## AttendanceCapture

### Changes

- Implemented `AttendanceCapture` as an abstract interface.
- Implemented the UML-specified capture operations as pure virtual functions.
- No `.cpp` file was created.
- Added a virtual destructor.

### Reason

`beginSession()`, `captureNext()`, and `endSession()` are pure virtual functions and therefore do not require concrete implementations in the abstract interface.

The virtual destructor allows concrete capture implementations to be safely destroyed through an `AttendanceCapture*`.

### UML / Code Deviations

1. No `.cpp` implementation file was added because the class contains only pure virtual operations.
2. A virtual destructor was added for safe polymorphic destruction.
3. No existing capture operation or relationship was removed.

---

## RotatingCodeCapture

### Changes

- Implemented `RotatingCodeCapture` as a derived class of `AttendanceCapture`.
- Implemented `beginSession()`, `captureNext()`, and `endSession()`.
- Added private `currentCode : string`.
- Updated `captureNext()` to validate the entered attendance code against the current active session code.

### Reason
The project requires a custom exception hierarchy for domain-level rule violations.

`currentCode` stores the currently generated attendance code during an active session.

Validation is implemented inside `captureNext()` without introducing a separate public validation method, keeping the existing interface unchanged.

### UML / Code Deviations

1. Added the private `currentCode : string` attribute.
2. No constructor was added because the UML does not specify one.
3. No additional rotation interval, timer, or code-generation attributes were added.
4. No new public validation method was added.
5. Invalid input returns an unsuccessful result without recording attendance.

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
`operator==` is used for equality and timetable clash detection, so a boolean return value is required.

`time_t` is used as the C++ representation of a time value.

The constructor initializes private attributes because the UML does not specify setter methods.

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

The percentage functions calculate attendance using the stored attendance information.

### UML / Code Deviations

1. `markpresent(Student student, AttendanceSession session)` uses `Student&` and `AttendanceSession&` in the implementation.
2. Percentage method parameters use references where necessary to identify existing Student and Course objects.
3. Added friend access where required by the attendance implementation.
4. Additional session-reference and correction/reporting integration was added later during final integration.

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
`Course` is abstract and therefore cannot be stored by value in the timetable.

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

## Generic Repository

### Changes

- Implemented `Repository<T>` with a file-path constructor and `load()`, `save()`, `add()`, and `remove()` operations.
- Used `vector<T>` internally for repository records.
- Implemented temporary-file replacement and backup creation during saving.
- Added directory handling and persistence-related exception handling.
- Template definitions remain in `Repository.h`.

### Reason
Course is abstract and cannot be stored directly as an object, so a pointer is used to refer to the associated Course.

The repository provides one reusable abstraction for text-file persistence while keeping file operations separate from the domain classes.

### UML / Code Deviations

1. The UML represents the repository using `list<T>`, while the implementation uses `vector<T>`.
2. The repository is header-only because it is a template.
3. Application integration uses `Repository<string>` line records rather than direct domain-object serialization.
4. Backup and temporary-file handling are implementation details and are not represented as separate UML classes.

### Approved by

Member 3 / Group integration decision.

---

## Person Persistence and Application Connection

### Changes

- Added `Menu` and `Administrator` as friends of `Person`.
- Added a non-owning `Menu* application`, initially `nullptr`.
- Added `setApplication(Menu*)`.
- Connected each user's role-specific interface to the application managing shared data and menus.

### Reason

The application needs controlled access to shared application state while keeping user data private.

### UML / Code Deviations

- Added friendship declarations.
- Added the non-owning `Menu* application` relationship.
- Added `setApplication(Menu*)`.
- Existing user attributes remain private.

### Approved by

Member 3 / Group integration decision.

---

## Menu Application State and Integration Interface

### Changes

- Added owned user and course collections and an `AttendanceRegister` to `Menu`.
- Added data path, current user and control flags.
- Added role handlers, lookup functions, persistence helpers, demo setup and reference checks.

### Reason

The application needs one place to manage live objects, authentication, role menus, persistence and cross-component relationships.

### UML / Code Deviations

- `Menu` contains `vector<unique_ptr<Person>>` and `vector<unique_ptr<Course>>`.
- `current` is a non-owning `Person*`.
- `AttendanceRegister` is contained by value.
- Expanded `Menu` beyond `run()` and `showloginmenu()` to support final application integration.
- The original operations remain.

### Approved by

Member 3 / Group integration decision.

---

## Drop Status and Enrolment History

### Changes

- Added Student and Menu friendship to Enrolment.
- `dropCourse()` marks an owned enrolment as `Dropped`.
- Dropping removes its active course reference and updates the timetable.
- `isEnrolled()` checks the student's owned enrolment records and requires the `Enrolled` status.
- Dropping without an active enrolment throws the existing `NotEnrolledException`.

### Reason
`currentCode` stores the currently generated attendance code during an active session.

The system must preserve enrolment history while distinguishing active enrolments from dropped or completed records.

### UML / Code Deviations

- Added friendship declarations.
- Existing enrolment status and public operation signatures remain.
- Historical enrolment records are retained rather than physically deleted.

### Approved by

Member 3 / Group integration decision.

---

## Prerequisite Integration Preparation

### Changes

- Implemented `Student::hasCompleted()` using the student's owned enrolment history and `Enrolment::isCompleted()`.
- Added `Course::getPrerequisites() const`.

### Reason

This replaced the placeholder implementation that always returned false and allowed prerequisite validation to inspect the existing prerequisite list without copying or modifying it.

### UML / Code Deviations

- Added a read-only `Course::getPrerequisites() const` getter.
- No new field, class or grading rule was introduced.

### Approved by

Member 3 / Group integration decision.

---

## Recursive Prerequisite Integration

### Changes

- Replaced the prerequisite TODO in `Student::enrollCourse()` with recursive validation.
- Direct and indirect prerequisites are checked.
- Missing prerequisite courses and detected prerequisite cycles are rejected.
- Integration uses `Menu::findCourse()` and `Course::getPrerequisites()`.
- Local sets track courses currently being checked and courses already checked.

### Reason

The enrolment workflow must enforce prerequisite chains rather than only checking direct prerequisites.

### UML / Code Deviations

- No additional class, persistent field, or public method was introduced.
- Cycle detection is implemented using local tracking sets.

### Approved by

Member 3 / Group integration decision.

---

## AssessmentMarks Ownership

### Changes

- `Enrolment` stores `AssessmentMarks` through `unique_ptr`.
- `setAssessmentMarks()` creates and owns the assessment-mark object.
- Declared the Enrolment destructor in the header and defined it in the implementation file.

### Reason
`time_t` provides a usable C++ representation for time values.

Assessment marks belong to an individual enrolment and require clear ownership.

Using `unique_ptr` provides RAII-based ownership and prevents references to destroyed temporary objects.

### UML / Code Deviations

- `Enrolment` explicitly owns its optional `AssessmentMarks`.
- The implementation uses `unique_ptr<AssessmentMarks>`.
- Assessment marks are not included in the final application persistence format.

### Approved by

Member 3 / Group integration decision.

---

## CorrectionRecord Lecturer Reference

### Changes

- `CorrectionRecord` stores a non-owning `Lecturer*` instead of a Lecturer value.
- Its constructor and AttendanceRegister correction operations accept `Lecturer&`.
- Deleted Lecturer copy constructor and copy assignment.

### Reason

Copying Lecturer would duplicate pointers to owned attendance sessions and could result in invalid ownership or double deletion.

The correction record therefore refers to the existing acting Lecturer without owning or copying it.

### UML / Code Deviations

- Acting Lecturer is represented as a non-owning pointer in the implementation.
- The relationship is therefore an association rather than ownership.
- Lecturer copy operations are disabled to protect resource ownership.

### Approved by

Member 3 / Group integration decision.

---

## Capture Forwarding and Source Identification

### Changes

- Added abstract `AttendanceCapture::name() const` and implementations in both concrete capture classes.
- Added `AttendanceSession::captureNext()` and `captureName() const`.
- Input capture rejects closed or expired sessions and sessions without a capture mechanism.
- AttendanceRegister records the actual capture source instead of fixed text.

### Reason
`time_t` is used as the C++ representation of a time value.

The UI needs to request attendance input through the session while keeping the session independent of concrete capture classes.

Attendance records should identify whether attendance was captured using the rotating-code or file-replay mechanism.

### UML / Code Deviations

- Added `AttendanceCapture::name() const`.
- Added `AttendanceSession::captureNext()`.
- Added `AttendanceSession::captureName() const`.
- Added corresponding concrete capture implementations.
- No new domain class was introduced.

### Approved by

Member 3 / Group integration decision.

---

## Attendance-Session Eligibility Snapshot

### Changes

- Added `eligibleStudentIds` to AttendanceSession.
- Added read-only `eligibleStudents()`.
- Opening a session snapshots the unique IDs of currently enrolled students.
- Move operations transfer the eligibility list with the session.
- Added Menu persistence access for session state.
- Explicitly deleted the copy constructor because the session owns its capture mechanism.
- Opening requires a course and positive duration.
- Capture initialization occurs before the session becomes open.

### Reason

Attendance percentages must account for students who were eligible when the session occurred, including students who never submitted attendance.

The snapshot preserves historical attendance eligibility after enrolment changes.

### UML / Code Deviations

- Added `eligibleStudentIds`.
- Added `eligibleStudents()`.
- Added persistence friendship/access.
- Added deleted copy construction.
- These additions support attendance history and resource ownership.

### Approved by

Member 3 / Group integration decision.

---

## Attendance Reporting and Correction Integration

### Changes

- AttendanceRegister keeps non-owning session references and provides `registerSession()`.
- Sessions with no attendance records can therefore participate in percentage calculations.
- Percentages use the eligible roster stored at session opening.
- Present and Late count as attended; Absent does not.
- Added `correct()`, `effectiveStatus()`, and `showAudit()`.
- CorrectionRecord stores `correctedStatus`.
- Corrections append information with the acting Lecturer, reason, timestamp and corrected status while preserving original records.
- Only the relevant course Lecturer may perform a correction.
- A correction for an unrecorded eligible student first creates an immutable Absent baseline.
- Added persistence access for attendance records, corrections and the register.

### Reason
The collections match the UML relationships.

To support attendance reporting while preserving immutable original attendance records and maintaining historical session eligibility.

### UML / Code Deviations

- Added session-reference collection to AttendanceRegister.
- Added `registerSession()`.
- Added `correct()`, `effectiveStatus()`, and `showAudit()`.
- Added `correctedStatus` to CorrectionRecord.
- Added Lecturer reference to CorrectionRecord.
- Added persistence friendship/access.
- These additions complete the attendance integration without introducing a separate attendance-reporting class.

### Approved by

Member 3 / Group integration decision.

---

# 2026-09-20 – Final Integration

## Menu – Persistent Application Reconstruction

### Changes

- Implemented loading of users, courses, enrolments, attendance sessions, attendance records, and correction records at startup.
- Relationships are reconstructed using saved identifiers so courses refer to the correct Lecturer, Enrolment objects refer to existing Student and Course objects, and attendance records refer to restored sessions.
- Implemented system-level saving through `Menu::save()` using `Repository<string>` line records.
- Added persistence helper operations to `Menu`.

### Reason

The final system must preserve users, courses, enrolments, attendance data, and relationships between program runs while keeping file I/O behind the repository abstraction.

### UML / Code Deviations

- `Menu` owns the live collections of users and courses and contains the application-level `AttendanceRegister`.
- Expanded `Menu` with persistence and application-state operations.
- Added application-level persistence helper operations.
- Added persistence access required to reconstruct private domain state.
- Application integration uses `Repository<string>` line records rather than direct domain-object serialization.

### Approved by

Group integration decision.

---

## User Persistence and Administrator CRUD

### Changes

- Added constructors that restore existing user IDs from files.
- `Person::nextId` is advanced when persisted IDs are loaded to prevent duplicate future IDs.
- Implemented Administrator create, update, and remove user operations with persistence and reference checks.
- Added application and persistence access required to restore and update private user state.

### Reason

User accounts must survive restart and Administrator must support the required account-management operations.

### UML / Code Deviations
- No UML class, attribute, relationship, or domain method was changed.

- Added persistence constructors accepting an existing ID.
- Added application/persistence friendship to `Person`.
- Added application-level access required for restoring private account fields and the ID counter.
- These are implementation-level persistence additions and do not change the fundamental user inheritance hierarchy.

### Approved by

Group integration decision.

---

## Course Persistence and Administrator Course CRUD

### Changes

- Extended the course text format to persist course type, code, title, credits, capacity, lecturer ID, prerequisite codes, and one or more time slots.
- Implemented Administrator create, edit, and remove course operations.
- Added reference protection so courses with enrolment history or prerequisite references are not unsafely removed.
- Editing a course preserves object relationships where possible.
- Changing derived course type is rejected when existing enrolment history would make replacement unsafe.

### Reason

The final implementation requires complete course management and correct reconstruction of lecturer, prerequisite and timetable relationships.

### UML / Code Deviations

- Added persistence-specific helper access without changing the underlying domain ownership model.
- Course persistence stores derived course type information so the correct concrete Course subclass can be reconstructed.
- Persistence format includes course time-slot information that is reconstructed into the Course TimeSlot collection.
- Administrator management operations are implemented at application level while the core Course hierarchy remains unchanged.

### Approved by

Group integration decision.

---

## Student Enrolment Integration

### Changes

- Connected Student menu operations to enrolment, drop, completion-check, and personal timetable functions.
- Implemented recursive prerequisite-chain validation with cycle detection.
- Timetable clash rejection uses the existing overloaded `TimeSlot::operator==`.
- Enrolment and drop changes are saved immediately.
- Dropped enrolments remain in the student's history while active-enrolment checks distinguish them from current enrolments.

### Reason

To complete the end-to-end Student workflow while keeping business rules in the domain classes rather than the menu driver.

### UML / Code Deviations

- The originally planned `enterAttendanceCode(string)` operation was not retained as a separate public method.
- The Student role menu obtains the attendance code through the active `AttendanceSession` interface and passes it to the attendance core.
- This preserves the responsibility without introducing a duplicate public wrapper.
- Recursive prerequisite validation uses implementation-level tracking sets for cycle detection.
- No additional domain class or persistent field was introduced.

### Approved by

Group integration decision.

---

## Lecturer Attendance Workflow and Runtime Capture Selection

### Changes

- Lecturer menu supports opening and closing attendance sessions, attendance reports, corrections, and correction-audit display.
- Added an overload of `openAttendanceSession` that accepts an `AttendanceCapture*` selected at runtime.
- Lecturer course-slot ownership is checked by exact slot fields rather than the overlap operator.
- `TimeSlot::operator==` therefore remains dedicated to timetable clash detection.
- Added `activeSession`, owned `sessionHistory`, and `getActiveSession()` to preserve session lifetimes used by attendance records.

### Reason

To support both mandatory attendance capture mechanisms safely and preserve attendance-session objects referenced by attendance records.

### UML / Code Deviations

- Added `sessionHistory : list<AttendanceSession*>`.
- Added the capture-injection overload of `openAttendanceSession`.
- Added `activeSession`.
- Added `getActiveSession() const`.
- Lecturer slot ownership validation uses explicit slot fields rather than `TimeSlot::operator==`.

### Approved by

Group integration decision.

---

## Attendance Core, Reporting, Corrections, and Persistence

### Changes

- `AttendanceRegister` tracks non-owning session references in addition to owned attendance records and correction records.
- Session opening snapshots the IDs of students actively enrolled at that time.
- Attendance validation rejects closed or expired sessions, non-enrolled students, and duplicate marks using distinct custom exceptions.
- Per-student and per-course percentages use eligible-session snapshots.
- Present and Late count as attended.
- Corrections append a `CorrectionRecord` containing corrected status, acting Lecturer, reason, and timestamp.
- Original `AttendanceRecord` objects are not edited or deleted.
- Attendance sessions, attendance records, and correction records are saved and restored across program runs.
- Expired sessions close their capture mechanism automatically.
- A correction for an eligible student with no existing attendance record first creates an immutable Absent baseline.

### Reason

To provide the required attendance core and preserve accurate historical attendance information after enrolment changes or program restart.

### UML / Code Deviations

- `AttendanceSession` gained an eligibility snapshot of student IDs.
- Added `eligibleStudents()` access.
- `AttendanceRegister` gained a non-owning session-reference collection.
- Added `registerSession()`.
- Added correction/reporting integration operations including `correct()`, `effectiveStatus()`, and `showAudit()`.
- `CorrectionRecord` gained `correctedStatus`.
- `CorrectionRecord` stores a non-owning `Lecturer*` reference rather than copying a Lecturer object.
- Added persistence friendship/access for attendance records, correction records and the register.
- Attendance percentages use the eligibility snapshot rather than only counting stored attendance records.
- Restored attendance sessions do not restore an active capture mechanism.

### Approved by

Group integration decision.

---

## FileReplayCapture and RotatingCodeCapture Final Integration

### Changes

- `FileReplayCapture` reads student IDs line-by-line.
- Replay line numbers are tracked for malformed-event reporting.
- `CorruptDataException` is thrown for malformed replay events.
- `RotatingCodeCapture` generates and validates a short session attendance code.
- Added `AttendanceCapture::name() const`.
- Both concrete mechanisms are selected at runtime through the `AttendanceCapture` base interface.
- Attendance records identify the capture mechanism used.

### Reason
These changes connect the Member 1 domain model with the Member 2 attendance implementation.

To provide interchangeable attendance-capture strategies and support the required replay test containing both valid and malformed events.

### UML / Code Deviations

- Added `AttendanceCapture::name() const`.
- Added corresponding `name()` implementations to `RotatingCodeCapture` and `FileReplayCapture`.
- Added `AttendanceSession::captureNext()`.
- Added `AttendanceSession::captureName() const`.
- Added capture forwarding through the abstract interface.
- `FileReplayCapture` contains implementation-specific `filePath`, `inputFile`, and `lineNumber` state.
- `RotatingCodeCapture` contains private `currentCode` state.
- These implementation details extend the UML representation without changing the core capture hierarchy.

### Approved by

Group integration decision.

---

## AttendanceSession Lifetime Integration

### Changes

- Updated Lecturer to retain closed `AttendanceSession` objects until the Lecturer is destroyed.
- Added private `sessionHistory : list<AttendanceSession*>`.
- Changed `closeAttendanceSession()` so that closing a session does not immediately delete the session object.
- Retained previous sessions when replacing an active session.
- Added cleanup of retained sessions in the Lecturer destructor.

### Reason

`AttendanceRecord` stores a pointer to its associated `AttendanceSession`.

Immediately deleting a closed session would leave existing AttendanceRecord objects with dangling `AttendanceSession*` pointers.

Closed sessions are therefore retained until the Lecturer is destroyed.

### UML / Code Deviations

- Added private `sessionHistory : list<AttendanceSession*>`.
- This represents an implementation-level ownership mechanism required to preserve the lifetime of sessions referenced by attendance records.
- The existing AttendanceRecord-to-AttendanceSession relationship remains non-owning.

### Approved by

Group integration decision.

---

## AttendanceRegister – Session Expiry Validation

### Changes

- Added an expiry check to `AttendanceRegister::markpresent()`.
- Attendance is rejected when the associated AttendanceSession has expired.
- `SessionClosedException` is thrown when an expired session is used to mark attendance.

### Reason

`AttendanceSession` provides `isExpired()` to determine whether the configured session duration has elapsed.

The AttendanceRegister must prevent attendance from being recorded after expiry.

### UML / Code Deviations

- No new UML relationship or domain attribute was introduced.
- The implementation uses the existing `AttendanceSession::isExpired()` operation.

### Approved by

Group integration decision.

---

## Administrator User and Course Reference Protection

### Changes

- Administrator user deletion checks existing references before removing users.
- Course deletion checks enrolment and prerequisite references before removal.
- Course editing preserves existing relationships where possible.

### Reason

Persistent objects are referenced by other domain objects. Removing them without checking references could leave invalid relationships.

### UML / Code Deviations

- Reference-protection logic is implemented at application/integration level.
- No additional domain class was introduced.
- Existing pointer-based relationships remain unchanged.

### Approved by

Group integration decision.

---

## AssessmentMarks Ownership

### Changes

- `Enrolment` stores `AssessmentMarks` through `unique_ptr`.
- `setAssessmentMarks()` creates and owns the assessment-mark object.
- The Enrolment destructor is explicitly declared and defined.

### Reason

Assessment marks belong to an individual enrolment and should have a clear ownership relationship.

Using `unique_ptr` provides RAII-based ownership and prevents references to destroyed temporary objects.

### UML / Code Deviations

- `Enrolment` explicitly owns its optional `AssessmentMarks`.
- The implementation uses `unique_ptr<AssessmentMarks>`.
- Assessment marks are not included in the final application persistence format.

### Approved by

Group integration decision.

---

## CorrectionRecord Lecturer Reference

### Changes

- `CorrectionRecord` stores a non-owning `Lecturer*`.
- Its constructor and AttendanceRegister correction operations accept `Lecturer&`.
- Lecturer copy construction and copy assignment are disabled.

### Reason

Copying a Lecturer would duplicate pointers to owned attendance sessions and could result in invalid ownership or double deletion.

The correction record therefore refers to the existing acting Lecturer without owning or copying it.

### UML / Code Deviations

- Acting Lecturer is represented as a non-owning pointer in the implementation.
- The UML relationship therefore represents an association rather than ownership.
- Lecturer copy operations are disabled to protect resource ownership.

### Approved by

Group integration decision.

---

## Attendance Capture Source Identification

### Changes

- Added abstract `AttendanceCapture::name() const`.
- Implemented the operation in both concrete capture classes.
- AttendanceSession forwards capture-source information.
- AttendanceRegister records the active capture mechanism rather than using a fixed source label.

### Reason

Attendance records should identify whether attendance was captured using the rotating-code or file-replay mechanism.

### UML / Code Deviations
1. Added private `sessionHistory : list<AttendanceSession*>`.

- Added `name()` to the abstract capture interface.
- Added corresponding concrete implementations.
- Added `captureName()` to AttendanceSession.
- Added capture-source forwarding without introducing a new domain class or attribute.

### Approved by

Group integration decision.

---

## Attendance-Session Eligibility Snapshot

### Changes

- Added `eligibleStudentIds` to AttendanceSession.
- Added read-only `eligibleStudents()` access.
- Opening a session snapshots the unique IDs of currently enrolled students.
- Move operations transfer the eligibility list with the session.
- Added Menu persistence access for session state.
- Added explicit deleted copy construction to document exclusive capture ownership.
- Validation requires a course and positive duration before opening.

### Reason

Attendance percentages must account for students who were eligible when the session occurred, including students who never submitted attendance.

The snapshot also preserves historical attendance eligibility after enrolment changes.

### UML / Code Deviations

- Added `eligibleStudentIds`.
- Added `eligibleStudents()`.
- Added persistence friendship/access.
- Added explicit deleted copy construction.
- These additions support attendance history and resource ownership without introducing a new class.

### Approved by

Group integration decision.

---

## Attendance Reporting and Correction Integration

### Changes

- AttendanceRegister maintains non-owning references to attendance sessions.
- Added `registerSession()` so sessions with no attendance records participate in percentage calculations.
- Attendance percentages use the eligible roster captured at session opening.
- Present and Late count as attended.
- Added `correct()`, `effectiveStatus()`, and `showAudit()`.
- Corrections preserve the original AttendanceRecord and append a CorrectionRecord.
- Only the relevant course Lecturer may perform a correction.
- A correction for an eligible student without an existing record creates an immutable Absent baseline.
- Attendance records, correction records, and session references are available to the persistence layer.

### Reason
`AttendanceSession` already provides the `isExpired()` operation.

To support attendance reporting while preserving immutable original attendance records and maintaining historical session eligibility.

### UML / Code Deviations

- Added session-reference collection to AttendanceRegister.
- Added `registerSession()`.
- Added `correct()`, `effectiveStatus()`, and `showAudit()`.
- Added `correctedStatus` to CorrectionRecord.
- Added Lecturer reference to CorrectionRecord.
- Added persistence access for attendance objects.
- These are implementation-level additions required to complete the attendance workflow.

### Approved by

Group integration decision.

---

## User Persistence and Administrator CRUD

### Changes

- Added constructors that restore existing user IDs from files.
- `Person::nextId` is advanced when persisted IDs are loaded to prevent duplicate future IDs.
- Implemented Administrator create, update, and remove user operations with persistence and reference checks.

### Reason

User accounts must survive restart and Administrator must support the required account-management operations.

---

- Added persistence constructors taking an existing ID.
- Added application/persistence friendship required to restore private state.
- Added application-level access required for restoring private account fields and the ID counter.

### Approved by

Group integration decision.

---

## Course Persistence and Administrator Course CRUD

### Changes

- Extended the course text format to persist course type, code, title, credits, capacity, lecturer ID, prerequisite codes, and one or more time slots.
- Implemented Administrator create, edit, and remove course operations.
- Added reference protection so courses with enrolment history or prerequisite references are not unsafely removed.
- Editing a course preserves object relationships where possible.
- Changing derived course type is rejected when existing enrolment history would make replacement unsafe.

### Reason

The final implementation requires complete course management and correct reconstruction of lecturer, prerequisite and timetable relationships.

### UML / Code Deviations

- Added persistence-specific helper access without changing the domain ownership model.
- Persistence stores derived course type information so the correct concrete Course subclass can be reconstructed.
- Persistence format includes course time-slot information.
- Administrator management is implemented at application level while the core Course hierarchy remains unchanged.

### Approved by

Group integration decision.

---

## Final Capacity and Expiry Corrections

### Changes

- `Course::isFull()` now counts active enrolments rather than completed historical enrolments.
- `AttendanceSession::isExpired()` closes the session when its configured duration has elapsed.
- Expiry causes attendance capture to stop accepting attendance.

### Reason

Completed students should not consume current course capacity, and session expiry must have the same closed-state effect as manual closure.

### UML / Code Deviations

- No new UML class or relationship was introduced.
- These are behavioural corrections to existing domain operations.

### Approved by

Group integration decision.

---

# Final Verification

The final integrated implementation was verified through targeted manual testing covering:

- attendance attempted without an open session;
- invalid rotating attendance code;
- valid and malformed FileReplayCapture events;
- non-enrolled attendance rejection;
- duplicate attendance rejection;
- timetable clash detection;
- session opening and runtime capture selection.

The final project was also built and launched using the configured C++17 CMake build.

No automated test suite is included in the repository.
