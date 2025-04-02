class Student:
    def __init__(self, name, roll, dept, address, gender, marks):
        self.name = name
        self.roll = roll
        self.dept = dept
        self.address = address
        self.gender = gender
        self.marks = marks
        self.total = sum(marks)
        self.percentage = self.total/(len(marks)*100)
    
    def display(self):
        print("\nStudent Details : ")
        print(f"Name        : {self.name}")
        print(f"Roll No.    : {self.roll }")
        print(f"Department  : {self.dept}")
        print(f"Address     : {self.address}")
        print(f"Gender      : {self.gender}")
        print(f"Marks       : {self.marks}")
        print(f"Total Marks : {self.total}")
        print(f"Percentage  : {self.percentage * 100}")

n = int(input("Enter number of students : "))
students = []

for i in range(n) : 
    name = input("Name : ")
    roll = int(input("Roll No : "))
    dept = input("Department : ")
    addr = input("Address : ")
    gender = input("Gender : ")
    marks = list(map(int, input(f"Enter marks in subject : ").split()))
    print("\n\n")
    students.append(Student(name, roll, dept, addr, gender, marks))

for student in students:
    student.display()

max_stud = max(students, key=lambda stud : stud.total)
min_stud = min(students, key=lambda stud : stud.total)
fal_stud = [stud for stud in students if any(m < 10 for m in stud.marks)]

print(f"\n\nStudent with maximum marks : ")
max_stud.display()
print(f"\n\nStudent with minimum marks : ")
min_stud.display()
print(f"\n\n{len(fal_stud)} Failed students : ")
for s in fal_stud:
    s.display()