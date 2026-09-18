    --------------------------------------------------- 
    | Date         | Change          |  Reason        |   
    ---------------------------------------------------
## 2026-09-18

### Person

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
3. A `virtual` destructor was added.
4. Private `generateId()` was added as an implementation helper.
5. UML uses `getname()`, `getid()`, and `showmenu()`, while the code uses `getName()`, `getId()`, and `showMenu()`.

These changes improve encapsulation, const-correctness, and safe polymorphism without adding new domain responsibilities.


2. 

## 2026-09-15

### Student

- Changed `enrollCourse(Course c)` to `enrollCourse(Course& course)`.
- Changed `dropCourse(Course c)` to `dropCourse(Course& course)`.
- Changed `isEnrolled(Course c)` to `isEnrolled(const Course& course) const`.
- Added `const` qualifiers to `hasCompleted()` and `viewTimetable()`.
- Added `~Student() override = default`.

### Reason

`Course` is an abstract class, so passing it by value is inappropriate because it can cause object slicing and prevent proper use of polymorphism. References allow the original `Course` object to be used without copying or slicing.

The `const` qualifiers were added to read-only functions to prevent them from modifying the `Student` object.

The virtual default destructor explicitly overrides the virtual destructor inherited from `Person` and ensures safe destruction of `Student` objects through the inheritance hierarchy.

3. 


## 2026-09-18

### Lecturer

- Changed `viewEnrolment(Course)` to `viewEnrolment(Course& course) const`.
- Changed `openAttendanceSession(TimeSlot)` to `openAttendanceSession(const TimeSlot& slot)`.
- Added `~Lecturer() override = default`.

### Reason

References avoid unnecessary copying of domain objects, while `const` ensures that read-only operations do not modify the Lecturer.

The virtual destructor supports safe destruction of Lecturer objects through the polymorphic `Person` base class.

### UML / Code Deviations

- `viewEnrolment()` uses a `Course&` and `const` qualifier instead of passing `Course` by value.
- `openAttendanceSession()` uses `const TimeSlot&` instead of passing `TimeSlot` by value.
- The virtual destructor is explicitly overridden in `Lecturer` for safe polymorphic destruction.

4. 
## 2026-09-18

### Administrator

- Changed `createCourse()` and `editCourse()` lecturer parameters from `Lecturer` to `Lecturer&`.
- Added `const` references for string and prerequisite-list parameters to avoid unnecessary copying.
- Changed `removeUser()` to return `bool` to indicate whether the removal was successful.
- Changed `removeCourse()` to return `string` for the course removal result.
- Added `~Administrator() override = default`.

### Reason

`Lecturer&` allows the existing Lecturer object to be referenced without creating an unnecessary copy. `const` references avoid copying input strings and prerequisite lists while preventing modification of the supplied arguments. The return values of `removeUser()` and `removeCourse()` allow the result of the operation to be reported. The virtual default destructor safely overrides the `Person` destructor.

5. 

## 2026-09-18

### Course - TimeSlot

- Changed the `Course` class `timeslot` attribute from `list<Timetable>` to `list<TimeSlot>`.
- Added `TimeSlot.h` to `Course.h`.
- Implemented the Course-TimeSlot relationship by storing `TimeSlot` objects directly inside `Course`.

### REASON

The design identifies the relationship between `Course` and `TimeSlot` as a composition relationship.

The original UML attribute was written as `list<Timetable>`, while `TimeSlot` represents an individual scheduled time. Therefore, `list<TimeSlot>` was used in the implementation to represent the Course-TimeSlot relationship directly.

The `Course-Timetable` aggregation relationship is kept separately, with `Timetable` managing references to courses rather than being used as the Course's TimeSlot collection.

6. 

## 2026-09-18

### AssessmentMarks and Course Grading Interface

- Added a new `AssessmentMarks` class to store student-specific assessment marks.
- Added `caScore`, `examScore`, `practicalMarks`, and `submissionScore` attributes to `AssessmentMarks`.
- Added a constructor to initialize the assessment marks.
- Set `caScore`, `examScore`, and `submissionScore` to `-1` initially to represent marks that have not yet been entered.
- Initialized `practicalMarks` as an empty list.
- Added setter methods for CA score, exam score, practical marks, and submission score.
- Added getter methods for CA score, exam score, practical marks, and submission score.
- Added validation to ensure all entered marks are within the valid range of 0 to 100.
- Added `invalid_argument` exceptions for invalid assessment marks.
- Changed the `Course::calculategrade()` function from `calculategrade()` to `calculategrade(const AssessmentMarks& marks)`.
- Added `AssessmentMarks` as a parameter to the Course grading function so that grading can use the assessment marks of a particular student.
- Associated `AssessmentMarks` with `Enrolment` because assessment marks are specific to a student's enrolment.

### REASON

The original design placed assessment-related attributes such as `practicalmarks` and `submissionscore` within specific Course subclasses. However, assessment marks are specific to individual students and should not be shared by all students enrolled in the same Course.

A separate `AssessmentMarks` class was introduced to store the assessment information belonging to an individual student's enrolment.

The value `-1` was used as the initial value for single assessment marks to distinguish marks that have not yet been entered from valid marks, since valid marks are restricted to the range 0 to 100. The practical marks collection is initially empty because no practical marks may have been entered yet.

Validation was added to prevent assessment marks outside the valid 0 to 100 range. An `invalid_argument` exception is thrown when an invalid mark is provided.

The `calculategrade()` interface was changed to accept an `AssessmentMarks` object so that each Course subclass can use the relevant assessment marks while maintaining specialized grading algorithms through runtime polymorphism.

`AssessmentMarks` is responsible for storing and validating assessment data, while the Course subclasses are responsible for calculating grades.

This design change will be reflected in the final UML diagram and final project report.

## 2026-09-18

### Course Relationships, Functions and Object Lifecycle

- Changed the `Course` class `enroledstudentdetails` attribute from `list<Enrolment>` in the UML to `list<Enrolment*>` in the implementation.

- Changed the `Course` class `asignlecturer` attribute from `Lecturer` in the UML to `Lecturer*` in the implementation.

- Changed the return type of `viewenrolment()` from `list<Enrolment>` in the UML to `list<Enrolment*>` in the implementation.

- Added `addTimeSlot(const TimeSlot& slot)` to allow TimeSlot objects to be added to a Course.

- Added `getTimeSlots()` to allow the TimeSlots associated with a Course to be accessed.

- Added `addEnrolment(Enrolment& enrolment)` to allow an existing Enrolment object to be associated with a Course.

- Added a `Course` constructor to initialize the Course attributes and its associated Lecturer and prerequisites.

- Added a virtual destructor to the `Course` class to support safe destruction of derived Course objects through the base `Course` class.

### REASON

The `Course` class maintains references to existing `Enrolment` objects rather than storing separate copies of them. Therefore, `list<Enrolment*>` was used to represent the associated enrolment objects.

Similarly, a Course is assigned an existing Lecturer rather than creating and owning the Lecturer. Therefore, `Lecturer*` was used so that the Course can maintain a reference to the assigned Lecturer.

The return type of `viewenrolment()` was changed consistently with the representation of the enrolment collection.

The `addTimeSlot()` and `getTimeSlots()` functions were added because the implementation stores the TimeSlot objects directly within the Course. These functions provide ways to add and access the TimeSlots associated with a Course.

The `addEnrolment()` function was added so that an existing Enrolment object can be stored in the Course's `list<Enrolment*>` collection. This allows the enrolment created during the student enrolment process to be associated with the relevant Course without creating a separate copy of the Enrolment object.

A constructor was added so that a Course object can be initialized with its required information, including course details, capacity, assigned Lecturer, and prerequisites.

A virtual destructor was added because `Course` is used as a base class for the Course hierarchy and supports runtime polymorphism. This allows derived Course objects to be safely destroyed through a `Course` base-class reference or pointer.

These changes will be reflected in the final UML diagram and final project report.

8. 

## 2026-09-18

### LectureCourse Implementation and Grading

- Implemented the `LectureCourse` class as a public derived class of `Course`.
- Added the `LectureCourse` constructor to initialize the inherited `Course` information, including course code, title, credit, capacity, assigned Lecturer, and prerequisites.
- Implemented the `calculategrade(const AssessmentMarks& marks)` function required by the `Course` grading interface.
- Used `AssessmentMarks` to obtain the student's CA score and examination score for grade calculation.
- Added validation to ensure that both the CA score and examination score have been entered before calculating the grade.
- Added `invalid_argument` exception handling when the required assessment marks have not been entered.
- Implemented the LectureCourse grading calculation using a project-defined weighting of 40% for CA and 60% for the final examination.
- Kept assessment marks outside the `LectureCourse` class because they are student-specific and are stored through `AssessmentMarks`.

### REASON

`LectureCourse` was implemented as a derived class of `Course` so that it can provide its own grading behaviour while following the Course hierarchy and supporting runtime polymorphism.

The constructor passes the common course information to the base `Course` constructor so that the inherited Course attributes can be properly initialized.

The grading function receives an `AssessmentMarks` object because CA and examination marks belong to an individual student's enrolment rather than to the Course itself.

Validation was added to prevent grade calculation when the required CA or examination mark has not yet been entered. The `AssessmentMarks` class uses `-1` to represent a mark that has not yet been entered, so the LectureCourse grading function checks for this condition before performing the calculation.

A 40% CA and 60% final examination weighting was selected as a project-defined grading assumption for LectureCourse. This weighting is an implementation/design assumption and is not being presented as an official university grading rule.

The assessment data remains separated from `LectureCourse` so that the same Course object can be used for multiple students while each student's assessment marks remain associated with their individual enrolment.

9. 

## 2026-09-18

### LabCourse Implementation and Grading

- Removed the `practicalmarks : list<double>` attribute from the `LabCourse` class.
- Added a `LabCourse` constructor to initialize the inherited `Course` information, including course code, title, credit, capacity, assigned Lecturer, and prerequisites.
- Implemented the `calculategrade(const AssessmentMarks& marks)` function for `LabCourse`.
- Changed the grading function to receive `AssessmentMarks` so that the practical marks of a particular student's enrolment can be used for grade calculation.
- Implemented the LabCourse grading calculation using the average of the entered practical marks.
- Added validation to prevent grade calculation when no practical marks have been entered.
- Added `invalid_argument` exception handling for an empty practical-mark list.

### REASON

The `practicalmarks` attribute was removed from `LabCourse` because practical marks are specific to individual students rather than being shared by all students enrolled in the course. The practical marks are therefore stored in `AssessmentMarks`, which is associated with the student's enrolment.

A constructor was added so that a `LabCourse` object can be initialized with the required Course information and pass that information to the base `Course` class.

The `calculategrade()` implementation uses the `AssessmentMarks` object to access the practical marks belonging to a particular student. The final LabCourse grade is calculated as the average of the entered practical marks.

Validation was added to prevent calculation when the practical-mark list is empty and to avoid division by zero. An `invalid_argument` exception is thrown when no practical marks have been entered.

The average-of-practical-marks calculation is a project-defined grading assumption and is not being presented as an official university grading rule.

These changes will be reflected in the final UML diagram and final project report.

10. 

## 2026-09-18

### ProjectCourse Implementation and Grading

- Removed the `submissionscore : double` attribute from the `ProjectCourse` class.
- Added a `ProjectCourse` constructor to initialize the inherited `Course` information, including course code, title, credit, capacity, assigned Lecturer, and prerequisites.
- Implemented the `calculategrade(const AssessmentMarks& marks)` function for `ProjectCourse`.
- Used `AssessmentMarks` to obtain the submission score belonging to a particular student's enrolment.
- Implemented the ProjectCourse grading calculation by using the student's submission score as the final grade.
- Added validation to prevent grade calculation when a submission score has not been entered.
- Added `invalid_argument` exception handling for a missing submission score.

### REASON

The `submissionscore` attribute was removed from `ProjectCourse` because the submission score is specific to an individual student rather than being shared by all students enrolled in the course. The submission score is therefore stored in `AssessmentMarks`, which is associated with the student's enrolment.

A constructor was added so that a `ProjectCourse` object can be initialized with the required Course information and pass that information to the base `Course` class.

The `calculategrade()` implementation uses the `AssessmentMarks` object to access the submission score belonging to a particular student. The submission score is used as the final ProjectCourse grade.

Validation was added to prevent grade calculation when the submission score has not been entered. An `invalid_argument` exception is thrown when the submission score is unavailable.

Using the submission score directly as the ProjectCourse grade is a project-defined implementation assumption because the project specification does not provide a specific ProjectCourse grading formula.

These changes will be reflected in the final UML diagram and final project report.


11. 
## 2026-09-18

### Enrolment

- Changed the `Enrolment` class `student` attribute from `Student` in the UML to `Student*` in the implementation.
- Changed the `Enrolment` class `course` attribute from `Course` in the UML to `Course*` in the implementation.
- Changed the `dateEnrolled` attribute from `date` in the UML to `string` in the implementation.
- Added an `AssessmentMarks* assessmentMarks` attribute to associate assessment marks with an Enrolment.
- Added `setAssessmentMarks(AssessmentMarks& marks)` to assign assessment marks to an Enrolment.
- Added `calculateGrade()` to calculate and store the student's grade using the associated Course's grading logic.
- Added `getStudent() const` to access the Student associated with an Enrolment.
- Added `getCourse() const` to access the Course associated with an Enrolment.
- Added a friend `operator<<` for displaying Enrolment information.

### Reason

The `Student*` and `Course*` pointers allow an Enrolment to refer to the existing Student and Course objects instead of creating separate copies.

The `dateEnrolled` value is currently represented as a `string` to keep the implementation simple without introducing an additional date class.

`AssessmentMarks` was introduced to keep student-specific assessment data separate from the Enrolment object while allowing the Enrolment to use those marks when calculating the final grade. The `setAssessmentMarks()` function associates the marks with the Enrolment, while `calculateGrade()` delegates the actual grading calculation to the associated Course.

`getStudent()` and `getCourse()` provide controlled access to the existing Student and Course relationships without exposing the private data members directly.

The `operator<<` was added to provide formatted output of Enrolment information.

### UML / Code Deviations

1. `Student` → `Student*`
2. `Course` → `Course*`
3. `date` → `string`
4. Added `AssessmentMarks* assessmentMarks`.
5. Added `setAssessmentMarks()`.
6. Added `calculateGrade()`.
7. Added `getStudent() const`.
8. Added `getCourse() const`.
9. Added `operator<<`.

These changes will be reflected in the final UML diagram and final project report.


12. 
## 2026-09-18

### Custom Exception Hierarchy

- Created a custom `Exception` base class derived from `std::runtime_error`.
- Added `CourseFullException` for course-capacity violations during enrolment.
- Added `PrerequisiteNotMetException` for prerequisite violations during enrolment.
- Added `TimetableClashException` for timetable-clash violations during enrolment.

### Reason

The project specification requires a hierarchy of custom exceptions for domain-level rule violations.

The project design uses separate exception classes for the main enrolment-rule violations so that each type of rejection can be identified and handled clearly.

`CourseFullException` is used when a course has reached its capacity.

`PrerequisiteNotMetException` is intended for prerequisite validation failures.

`TimetableClashException` is intended for timetable conflicts during enrolment.

These exception classes are a design choice used to satisfy the project's custom exception requirement and provide clear domain-level error handling.

### UML / Code Deviations

- Added the custom exception hierarchy to support the required domain-level rule validation.
- Added `CourseFullException`, `PrerequisiteNotMetException`, and `TimetableClashException` as concrete exception types.

These additions will be reflected in the final UML diagram and project report.






