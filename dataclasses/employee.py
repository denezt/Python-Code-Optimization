#!/usr/bin/env python

class Employee:
    def __init__(self, name, job, age):
        self.name = name
        self.job = job
        self.age = age

empA = Employee("Peterle", "Senior Software Developer", 34)
empB = Employee("Werner", "Programmer", 24)
empC = Employee("Werner", "Programmer", 24)

print(id(empC))
print(id(empB))
print(empA)

print(empB == empC)
