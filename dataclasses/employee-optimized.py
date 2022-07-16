#!/usr/bin/env python

from dataclasses import dataclass, field

@dataclass(order=True,frozen=False)
class Employee:
    sort_index: int = field(init=False, repr=False)
    name: str
    job: str
    age: int
    time_employed: int = 10

    def __post_init__(self):
        object.__setattr__(self, 'sort_index', self.time_employed)

    def __str__(self):
        return f'Name: {self.name} ({self.age}), Works as: {self.job}, Employed for {self.time_employed} years.'


empA = Employee("Peterle", "Senior Software Developer", 35, 5)
empB = Employee("Werner", "Programmer", 25)
empC = Employee("Werner", "Programmer", 25)

print(empA)
print(id(empB))
print(id(empC))
# Now you can compare the values
print(empC == empB)
print(empA > empB)
