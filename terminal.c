#include<stdio.h>
#include<string.h>
#include<time.h>
#include"terminal.h"
#include"card.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData) {
	uint8_t day, month, tempDate[11];
	uint16_t year;
	time_t currentDate;
	time(&currentDate);
	struct tm* nowPtr = localtime(&currentDate);
	day = nowPtr ->tm_mday;
	month = nowPtr->tm_mon + 1;
	year = nowPtr->tm_year + 1900;

	sprintf(&tempDate, "%02d/%02d/%d", day, month, year);
	for (int i = 0; i <= strlen(tempDate); i++)
		termData->transactionDate[i] = tempDate[i];
	return OK_term;
}
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData) {
	
	uint8_t cardExpMon, transMon, cardExpYear, transYear;

	cardExpMon = cardData.cardExpirationDate[0] + cardData.cardExpirationDate[1] - 96;
	cardExpYear = cardData.cardExpirationDate[3] + cardData.cardExpirationDate[4] - 96;
	transMon = termData.transactionDate[3] + termData.transactionDate[4] - 96;
	transYear = termData.transactionDate[8] + termData.transactionDate[9] - 96;
	if (cardExpYear > transYear || (cardExpYear == transYear && cardExpMon > transMon))
		return OK_term;
	else
		return EXPIRED_CARD;

}

EN_terminalError_t isValidCardPAN(ST_cardData_t* cardData) {

}

EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData) {
	float tempAmount;
	printf("Please Enter the Transaction Amount: ");
	scanf("%f", &tempAmount);
	if (tempAmount <= 0)
		return INVALID_AMOUNT;
	else
		termData->transAmount = tempAmount;
		return OK_term;
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData) {
	float tempMaxAmount;
	printf("terminal maximum amount is: ");
	scanf("%f", &tempMaxAmount);
	if (tempMaxAmount <= 0)
		return INVALID_MAX_AMOUNT;
	else
		termData->maxTransAmount = tempMaxAmount;
		return OK_term;
}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData) {
	if (termData->transAmount > termData->maxTransAmount)
		return EXCEED_MAX_AMOUNT;
	else
		return OK_term;
}



