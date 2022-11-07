#include "app.h"

void appStart(void) {
	ST_cardData_t cardData;
	EN_cardError_t cardError;
	ST_terminalData_t termData;
	EN_terminalError_t terminalError;
	EN_serverError_t serverError;
	EN_transStat_t transactionError;
	ST_transaction transData;

	do
	{
		cardError = getCardHolderName(&cardData);
		if (cardError == WRONG_NAME)
			printf("Wrong Name Format\n");
		else if (cardError == OK_card)
			printf("OK\n");
		else {
			printf("uknown Name Error\n");
			return 0;
		}
	} while (cardError != OK_card);

	do
	{
		cardError = getCardExpiryDate(&cardData);
		if (cardError == WRONG_EXP_DATE)
			printf("Wrong Date Format\n");
		else if (cardError == OK_card)
			printf("OK\n");
		else {
			printf("uknown ExpDate Error\n");
			return 0;
		}
	} while (cardError != OK_card);

	do
	{
		cardError = getCardPAN(&cardData);
		if (cardError == WRONG_PAN)
			printf("Wrong PAN Format\n");
		else if (cardError == OK_card)
			printf("OK\n");
		else {
			printf("uknown PAN Error\n");
			return 0;
		}
	} while (cardError != OK_card);

	do
	{
		terminalError = setMaxAmount(&termData);
		if (terminalError == INVALID_MAX_AMOUNT)
			printf("Invalid max amount\n");
		else if (terminalError == OK_term)
			printf("OK\n");
		else {
			printf("Uknown MaxAmount Error\n");
			return 0;
		}
	} while (terminalError != OK_term);

	terminalError = getTransactionDate(&termData);
	if (terminalError == WRONG_DATE)
		printf("Wrong Date\n");
	else if (terminalError == OK_term)
		printf("Transaction Date is Now\n");
	else {
		printf("Uknown Transaction Date Error\n");
		return 0;
	}
	terminalError = isCardExpired(cardData, termData);
	if (terminalError == EXPIRED_CARD) {
		printf("Expired Card\n");
		return 0;
	}
	else if (terminalError == OK_term)
		printf("OK\n");
	else {
		printf("Uknown ExpDate Error\n");
		return 0;
	}

	do
	{
		terminalError = getTransactionAmount(&termData);
		if (terminalError == INVALID_AMOUNT)
			printf("invalid Amount\n");
		else if (isBelowMaxAmount(&termData) == EXCEED_MAX_AMOUNT)
			printf("Exceeded MAX Amount\n");
		else if (terminalError == OK_term && isBelowMaxAmount(&termData) == OK_term)
			printf("OK\n");
		else {
			printf("Uknown transAmountError");
			return 0;
		}
	} while (terminalError != OK_term || isBelowMaxAmount(&termData) != OK_term);

	transData.terminalData = termData;
	transData.cardHolderData = cardData;

	serverError = recieveTransactionData(&transData);
	if (serverError == DECLINED_STOLEN_CARD)
		printf("Declined, This card is reported to be stolen!");
	else if (serverError == DECLINED_INSUFFECIENT_FUND)
		printf("Declined, Your Balance is insuffecient");
	else if (serverError == INTERNAL_SERVER_ERROR)
		printf("Internal Server Error");
	else
		printf("Your Transaction is Successfull");
	return 0;
}