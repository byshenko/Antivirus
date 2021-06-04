# A simple Qt5 Antivirus

A simple antivirus written using the Qt5 libraries and the C++language. This antivirus tries to be portable to any platform to minimize development costs.

## Task List

:ballot_box_with_check: non-terrible appearance

:black_square_button: signature analysis

:black_square_button: collecting and displaying logs

:black_square_button: using updates

:black_square_button: additional features

## Basic Terms

***Signature-based detection*** is a method of operation of antivirus and intrusion detection systems, in which a program, viewing a file or package, accesses a dictionary with known viruses compiled by the authors of the program. If any part of the code of the program being viewed matches the known code (signature) of the virus in the dictionary, the antivirus program can perform one of the following actions:

 - Delete the infected file.
 - Send the file to "quarantine" (that is, make it unavailable for execution, in order to prevent the further spread of the virus).
 - Try to restore the file by removing the virus itself from the file body.

A ***quarantine*** is a special storage where objects that may be infected with viruses are placed. "Possibly infected objects" refers to objects suspected of being infected with viruses and their modifications. Such objects are quarantined automatically and do not pose a threat to your computer.

