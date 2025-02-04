# Windows Administative Rigths checks

## Overview
This project is a C++ application that compiles using C++14.
It is designed to make some simple checks on the local PC to ensure that the user is running with a save administrative account.
This solution could be useful in case of you might need to ensure that the user is not using the system built-in Administrative account or the user have not disable the User Account Control.

## Description

Do you have discovered that some of your customer are using the system built-in Administrative or disable the UAC on all of their PCs and want to explain them why its dangerous?
Take a look a this code, and implement it in your software to make some simple checks on the local PC to ensure that the user is running with a safe administrative account.

## Checks
Here are the checks that this code will perform:

### Usage of builtin Administrator account
Why the Built-in Administrator Account is Risky:
* `High Privileges`: The built-in Administrator account has full control over the system. If compromised, an attacker can do anything to the computer.
* `Target for Attacks`: Because this account is well-known, it is a common target for hackers.
* `No Accountability`: Actions performed by this account are harder to trace back to a specific user, making it difficult to track changes or identify problems.

Here are the main differences between a standard administrative account and the built-in Administrator account in Windows:

* `Privileges and Control`:
  * Built-in Administrator Account: Has full control over the system without restrictions. It is not subject to User Account Control (UAC), which means it can perform any operation without prompting for confirmation.
  * Standard Administrative Account: Has high privileges, but is subject to User Account Control (UAC). This means that some operations require confirmation or the entry of administrative credentials.
* `Security`:
  * Built-in Administrator Account: This is a common target for cyber attacks because it is a well-known account and has unlimited privileges.
  * Standard Administrative Account: This is safer for everyday use because critical operations require confirmation, reducing the risk of malicious actions being performed without authorization.
* `Usage`:
  * Built-in Administrator Account: Generally disabled by default in modern versions of Windows and should only be used for maintenance or emergency purposes.
  * Standard Administrative Account: Used for day-to-day system management and to perform tasks that require elevated privileges.

### Disabling User Account Control (UAC)
Disabling User Account Control (UAC) is not recommended for several reasons related to system security.
Here are the main ones:
* `Prevent Unauthorized Changes`: UAC helps prevent applications, users, viruses, or other forms of malware from making unauthorized changes to the operating system. This is essential to maintaining the integrity and security of the system.
Reduced Malware Risk: UAC requires administrator approval to perform operations that could compromise the security of the system. Without UAC, malware and other threats could perform malicious operations without any restrictions.

* `Principle of Least Privilege`: UAC is based on the principle of least privilege, which suggests that users and applications should only use the privileges necessary to perform their tasks. This reduces the risk of accidental or intentional damage to the system.

* `More Control`: UAC provides an additional level of control, allowing administrators to monitor and approve critical changes to the system. This is especially useful in corporate environments or situations where security is a priority.

## Requirements
- C++14 compatible compiler

## Build
1. Clone the repository
2. Build the solution
