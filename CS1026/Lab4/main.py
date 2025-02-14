# Name: Raymond Xie
# Description: Lab 04
# Date: 2022/10/10

# Q1
def factorial(n):
    result = n
    # Starts at n, ends at 1, and counts down by 1 each time
    for i in range(n, 0, -1):
        n -= 1
        # Makes sure that 0 is not multiplied into the result
        if n > 0:
            result = result * n
    return result


num = int(input("Please enter a number: "))
print(factorial(num))

# Q2
def helloWorld():
    print("Hello World")


def helloWorldNTimes(n):
    for i in range(n):
        helloWorld()


def main():
    helloWorldNTimes(2)
    helloWorldNTimes(1)
    helloWorldNTimes(3)
    helloWorldNTimes(2)

main()

# Q3
def countVowels(word):
    # Error 1: Should be 0 to start off
    numVowels = 0
    # Error 2: string needs to be changed to word to match the parameter name
    for letter in word:
        # Error 3: Need to add capital letters into the string as well so the code doesn't skip over them
        if letter in "aeiouAEIOU":
            numVowels += 1
    # Error 4: Return numVowels, not letter to get the vowel count
    return numVowels


print(countVowels("AEIOu"))