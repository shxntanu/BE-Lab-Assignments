# Assignment 4

## Title

Write a program in solidity to create Student data. Use the following constructs:
- Structures
- Arrays
- Fallback
Deploy this as smart contract on Ethereum and Observe the transaction fee and Gas values.

## Steps

1. Go to [Remix IDE](https://remix.ethereum.org/).

    ![image](https://github.com/user-attachments/assets/473734af-7376-4c8a-b554-ef083c1e63ed)

2. In the "File Explorer" tab, click the + icon to create a new file. Name the file `StudentData.sol`.

3. Copy the following code into the file

    ```sol
    // SPDX-License-Identifier: MIT
    pragma solidity ^0.8.0;
    
    contract StudentData {
        // Define a structure to hold student details
        struct Student {
            string name;
            uint256 age;
            string class;
            uint256 rollNumber;
        }
    
        // An array to hold all students
        Student[] public students;
    
        // Event to log student data when added
        event StudentAdded(string name, uint256 rollNumber);
    
        // Function to add a new student
        function addStudent(string memory _name, uint256 _age, string memory _class, uint256 _rollNumber) public {
            Student memory newStudent = Student({
                name: _name,
                age: _age,
                class: _class,
                rollNumber: _rollNumber
            });
            
            students.push(newStudent);
    
            // Emit an event to log the new student addition
            emit StudentAdded(_name, _rollNumber);
        }
    
        // Function to retrieve the total number of students
        function getTotalStudents() public view returns (uint256) {
            return students.length;
        }
    
        // Function to retrieve a student's details by index
        function getStudent(uint256 index) public view returns (string memory, uint256, string memory, uint256) {
            require(index < students.length, "Invalid index");
            Student memory student = students[index];
            return (student.name, student.age, student.class, student.rollNumber);
        }
    
        // Fallback function to handle any Ether sent to the contract
        fallback() external payable {
            // Any Ether sent to this contract will be accepted
        }
    
        // Function to check the balance of Ether in the contract
        function getContractBalance() public view returns (uint256) {
            return address(this).balance;
        }
    }
    ```

4. In the left sidebar, click on the Solidity Compiler (the "Compile" tab). Ensure the compiler version is set to `0.8.0` or higher (since we're using `^0.8.0` in the contract).
   
    Click the Compile Bank.sol button. If there are no errors, the contract will compile successfully.

5. Deploy the contract

    ![image](https://github.com/user-attachments/assets/0eaeeac9-a11f-4d59-afd3-9148b1d601a5)

6. Interact with the contract

    ![image](https://github.com/user-attachments/assets/9f1190f0-0a17-4f05-a140-efc1df6d9b9b)

