/*Written by: Bryan, Morvan, Ricky, Connor, Ian (Group 4)
10/20/2013
Purpose:Payroll with struct
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define pause system ("pause")
#define cls system ("cls")
#define CSIZE 50
#define flush fflush(stdin)
#define PAYHOURS 40

/*typedef struct{//declaring a struct
int month;
int day;
int year;
} DATE;*/ //this struct for numeric payDate rather than a string data type for date. There may be a DATE data type?

typedef struct{//declaring a struct
	char firstName [40];
	char lastName [40];
	char payDate[11];//we will have to use another struct to hold day/month/year as int
	double hourlyRate;
	double hoursWorked;
	double regularPay;
	double overTimePay;
	double grossPay;

} EMPLOYEE;//end struct EMPLOYEE

//Function Headers/Protoypes
int displayMenu();
void addEmployee (EMPLOYEE[], int *empNum);
void printEmployeeReport (EMPLOYEE[], int empNum);
void printAllEmployeesReport (EMPLOYEE[], int empNum); 
void printCompanyPayrollTotal(EMPLOYEE[], int empNum);
int readCompanyData(EMPLOYEE company[]);
void saveCompanyData(EMPLOYEE company[], int empNum);

main(){
	int empNum = 0, choice = 0;
	//DATE payDate;
	
	EMPLOYEE company[CSIZE];//create an array of structs as the data type

	empNum = readCompanyData(company);//had to assign empNum the value from the file via pass by value in readCompanyData function, cuz pass by reference wasn't working like I believe it should.
	
	do{
		choice = displayMenu();//incorporates getting user choice and error checking the choice.
		switch(choice){
		case 1:
			addEmployee(company, &empNum);
			break;
		case 2:
			printEmployeeReport(company, empNum);
			break;
		case 3:
			printAllEmployeesReport(company, empNum);
			break;
		case 4:
			printCompanyPayrollTotal(company, empNum);
			break;
		case 5:
			saveCompanyData(company, empNum);//the current EMPLOYEE company array is written into the file. Using "wb", it destroys the old data and rewrites a totally new file/data set.
			break;
		}//end switch	
	}while(choice != 5);
	pause;
}//end Main

void addEmployee (EMPLOYEE company[], int *empNum){//int*empNum points to empNum by position in the call.
	char tempFirstName[40] = "";// not sure struct variables need be initialized.
	char tempLastName[40] = "";
	char tempPayDate[11] = "";
	company[*empNum].regularPay = 0.0;
	company[*empNum].overTimePay = 0.0;
	company[*empNum].hourlyRate = 0.0;
	company[*empNum].hoursWorked = 0;

	printf("Enter First Name of Employee:\n");
	scanf("%s", &tempFirstName);
	flush;
	printf("Enter Last Name of Employee:\n");
	scanf("%s", &tempLastName);
	flush;
	printf("Enter the Pay Date (MM/DD/YYYY):\n");//could error check valid date ranges if int struct DATE was used
	scanf("%s", &tempPayDate);
	flush;
	strcpy(company[*empNum].firstName, tempFirstName);//strcpy to move a string to a char pointer
	strcpy(company[*empNum].lastName, tempLastName);
	strcpy(company[*empNum].payDate, tempPayDate);

	printf("Enter hourly pay rate for %s %s: \n", company[*empNum].firstName, company[*empNum].lastName);
	scanf("%lf", &company[*empNum].hourlyRate);
	printf("Enter hours worked for %s %s: \n", company[*empNum].firstName,company[*empNum].lastName);
	scanf("%lf", &company[*empNum].hoursWorked);

	if (company[*empNum].hoursWorked > PAYHOURS){
		company[*empNum].regularPay = PAYHOURS * company[*empNum].hourlyRate;
		company[*empNum].overTimePay = (company[*empNum].hoursWorked - PAYHOURS) * company[*empNum].hourlyRate * 1.5;
		company[*empNum].grossPay = company[*empNum].regularPay + company[*empNum].overTimePay;
	}else {
		company[*empNum].regularPay = company[*empNum].hourlyRate * company[*empNum].hoursWorked;
		company[*empNum].overTimePay = 0;
		company[*empNum].grossPay = company[*empNum].regularPay;
	}//end if else for calculating employee pay.

	(*empNum)++;//dereference with paranthesis first.

}//end addEmployee

int displayMenu(){
	int result = 0;

	do{
		cls;
		printf("Welcome to Optimus Programming Payroll Plus\n");
		printf("   1.Enter employee payroll information\n");
		printf("   2.Display payroll for an employee\n");
		printf("   3.Display payroll for all employees\n");
		printf("   4.Display total payroll for the company\n");
		printf("   5.Exit Payroll by Optimus Programming\n");
		printf("Please make a valid selection:");
		scanf("%i", &result);
		flush;

		if (result <1 || result > 5){
			cls;
			printf("Please make a valid selection!\n");
			pause;
		}// end if

	}while (result < 1 || result > 5);//end do while. Error check for invalid menu selectio.
	cls;

	return result;

}//end displayMenu

void printAllEmployeesReport (EMPLOYEE company[], int empNum){
	int i = 0;

	printf("Reports for all Employees:\n\n");

	if(empNum == 0)//error checking for no employee records
		printf("There are no reports to print.\n\n");
	else 
		for(i = 0; i < empNum; i++){
			printf("Name: %s %s \n", company[i].firstName, company[i].lastName );
			printf("Pay Date: %s\n", company[i].payDate);
			printf("Hourly Rate: $%.2lf \n", company[i].hourlyRate);
			printf("Hours Worked: %.1lf \n", company[i].hoursWorked);
			printf("Regular Pay: $%.2lf \n", company[i].regularPay);
			printf("Over Time Pay: $%.2lf \n", company[i].overTimePay);
			printf("Gross Pay: $%.2lf\n", company[i].grossPay);
			printf("\n");
		}//end for loop
		pause;

}//end printCompanyReport

void printCompanyPayrollTotal(EMPLOYEE company[], int empNum){
	int i = 0;
	double totalHours = 0, totalRegPay = 0, totalOT = 0, totalGross = 0;

	for(i = 0; i < empNum; i++){
		totalHours += company[i].hoursWorked;
		totalRegPay += company[i].regularPay;
		totalOT += company[i].overTimePay;
		totalGross += company[i].grossPay;
	}//end for loop

	printf("Totals for the Company are:\n\n");
	printf("Total man hours worked: %.1lf\n", totalHours);
	printf("Total for Reg Pay: $%.2lf\n", totalRegPay);
	printf("Total for OT Pay: $%.2lf\n", totalOT);
	printf("Total for Gross Pay: $%.2lf\n", totalGross);
	pause;

}//end printCompanyPayrollTotal

void printEmployeeReport (EMPLOYEE company[], int empNum){
	int i = 0, reportNum = 0;
	cls;
	if(empNum == 0)
		printf("There are no reports to print.\n\n");
	else {
		for (i = 0; i < empNum; i++){
			printf("%i:%s %s\n", i, company[i].firstName, company[i].lastName);
		}//end for

		printf("Please choose an employee report to print:\n");
		scanf("%i", &reportNum);
		flush;
		if(reportNum < empNum){//will prevent user from printing a screen of garbage if they choose an array element that has nothing in it.
		cls;
		printf("Employee Report\n\n");
		printf("Name: %s %s \n", company[reportNum].firstName, company[reportNum].lastName );
		printf("Pay Date: %s\n", company[reportNum].payDate);
		printf("Hourly Rate: $%.2lf \n", company[reportNum].hourlyRate);
		printf("Hours Worked: %.1lf \n", company[reportNum].hoursWorked);
		printf("Regular Pay: $%.2lf \n", company[reportNum].regularPay);
		printf("Over Time Pay: $%.2lf \n", company[reportNum].overTimePay);
		printf("Gross Pay: $%.2lf\n", company[reportNum].grossPay);
		}//end if
		else 
			printf("Invalid employee number!\n");//keeps peeps from trying to print an empoyee that doesn't exist.
	
	}//end else error check for no employee records

	pause;
}//end printEmployeeReport

void saveCompanyData(EMPLOYEE company[], int empNum){
	
	FILE* fp1;

	fp1 = fopen ("company.bin", "wb");//using "wb" here is acceptable because we want it to destroy all the data and just rewrite everything from the array that is current during current session. 
	fwrite(&empNum, sizeof(int), 1, fp1);
	fwrite(company, sizeof(EMPLOYEE), empNum, fp1);//writes EMPLOYEE customer array of structs to the bin file.
	fclose (fp1);
}//end saveCompanyData

int readCompanyData(EMPLOYEE company[]){
	int num = 0;
	FILE *fp1;

	fp1 = fopen ("company.bin", "ab+");//opening file with "ab+" preserves the data in it, and allows it to be written into the array for this program session.
	if(fp1 == NULL){                   //as is, with no path, it is created in the project folder of Visual Studios
		printf("Failed to create file!\n");
		exit(-1);//close program if file isn't created.
	}
	else 
		printf("File created successfully!\n");
	fclose(fp1);

	fp1 = fopen("company.bin", "ab+");
	fread(&num, sizeof(int), 1, fp1);
	fread (company, sizeof(EMPLOYEE), num, fp1);//i had to make this num variable because for some reason I couldn't get it to assign *empNum 
	fclose (fp1);
	return num;//returns the number of employess at the function call, which will facilitate in loading the correct empNum when the program is opened after a file is created.

}//end readCompanyData