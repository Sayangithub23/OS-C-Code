#!/bin/bash

# 1. Check if a number is even or odd
checkEvenOdd() {
    echo -n "Enter a number: "
    read num
    if ((num % 2 == 0)); then
        echo "$num is an even number."
    else
        echo "$num is an odd number."
    fi
}

# 2. Check if a year is a leap year
checkLeapYear() {
    echo -n "Enter a year: "
    read year
    if (( (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0) )); then
        echo "$year is a leap year."
    else
        echo "$year is not a leap year."
    fi
}

# 3. Calculate factorial of a number
findFactorial() {
    echo -n "Enter an integer: "
    read n
    
    if ((n < 0)); then
        echo "Factorial of a negative number doesn't exist."
    else
        factorial=1
        for ((i = 1; i <= n; i++)); do
            factorial=$((factorial * i))
        done
        echo "Factorial of $n = $factorial"
    fi
}

# 4. Swap two integer values
swapIntegers() {
    echo -n "Enter first integer (a): "
    read a
    echo -n "Enter second integer (b): "
    read b
    
    echo "Before swapping: a = $a, b = $b"
    
    # Swap logic
    temp=$a
    a=$b
    b=$temp
    
    echo "After swapping:  a = $a, b = $b"
}

# 5. Simple Calculator
simpleCalculator() {
    echo -n "Enter first number: "
    read n1
    echo -n "Enter an operator (+, -, *, /): "
    read op
    echo -n "Enter second number: "
    read n2

    # Use 'bc -l' for floating point arithmetic
    result=$(echo "$n1 $op $n2" | bc -l)
    
    if [ $? -eq 0 ]; then
        # Format to 2 decimal places
        printf "%.2f %s %.2f = %.2f\n" $n1 "$op" $n2 $result
    else
        echo "Error! Invalid input or division by zero."
    fi
}

# 6. Multiplication Table
multiplicationTable() {
    echo -n "Enter an integer to display its multiplication table: "
    read n
    echo "Multiplication table for $n:"
    for ((i = 1; i <= 10; i++)); do
        echo "$n * $i = $((n * i))"
    done
}

# 7. File existence check
checkFileExists() {
    echo -n "Enter filename to check: "
    read filename

    # [ -f "$filename" ] checks if the file exists and is a regular file
    if [ -f "$filename" ]; then
        echo "File '$filename' exists."
    else
        echo "File '$filename' does not exist."
    fi
}

# 8. Palindrome check
checkPalindrome() {
    echo -n "Enter a string: "
    read str
    
    # 'rev' command reverses a string
    reversed_str=$(echo "$str" | rev)
    
    if [ "$str" == "$reversed_str" ]; then
        echo "'$str' is a palindrome."
    else
        echo "'$str' is not a palindrome."
    fi
}

# 9. Sum of digits
sumOfDigits() {
    echo -n "Enter an integer: "
    read n
    
    sum=0
    num=$(( n < 0 ? -n : n )) # Handle negative numbers
    
    while ((num > 0)); do
        remainder=$((num % 10))
        sum=$((sum + remainder))
        num=$((num / 10))
    done
    
    echo "Sum of digits = $sum"
}

# 10. Count the number of words in a file
countWordsInFile() {
    echo -n "Enter filename: "
    read filename

    if [ ! -f "$filename" ]; then
        echo "Error: File '$filename' not found."
        return
    fi
    
    # 'wc -w' counts words
    # '< "$filename"' redirects file content as standard input
    wordCount=$(wc -w < "$filename")
    
    # wc -w output has leading spaces, so echo it to clean it up
    echo "Number of words in file '$filename': $wordCount"
}


# Main function with menu
main() {
    while true; do
        echo
        echo "--- OS Lab Menu (Bash Scripts) ---"
        echo "1.  Check Even or Odd"
        echo "2.  Check Leap Year"
        echo "3.  Calculate Factorial"
        echo "4.  Swap Two Integers"
        echo "5.  Simple Calculator"
        echo "6.  Multiplication Table"
        echo "7.  Check File Existence"
        echo "8.  Check Palindrome"
        echo "9.  Sum of Digits"
        echo "10. Count Words in a File"
        echo "0.  Exit"
        echo -n "Enter your choice: "
        
        read choice

        case $choice in
            1) checkEvenOdd ;;
            2) checkLeapYear ;;
            3) findFactorial ;;
            4) swapIntegers ;;
            5) simpleCalculator ;;
            6) multiplicationTable ;;
            7) checkFileExists ;;
            8) checkPalindrome ;;
            9) sumOfDigits ;;
            10) countWordsInFile ;;
            0) echo "Exiting program."; exit 0 ;;
            *) echo "Invalid choice. Please try again." ;;
        esac
        
        echo
        echo -n "Press Enter to continue..."
        read
    done
}

# Run the main function
main
