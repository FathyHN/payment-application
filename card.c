#include<stdio.h>
#include<string.h>
#include"card.h"

EN_cardError_t getCardHolderName(ST_cardData_t* cardData) {
	uint8_t tempName[50] = "NaN";
	printf("Please Enter the Card Holder Name: ");
	gets(tempName);
	uint16_t len = strlen(tempName);
	if (len < 12 || len > 24)
		return WRONG_NAME;
	else {
		for (int i = 0; i < len + 1; i++)
			if (!((tempName[i] >= 'A' && tempName[i] <= 'Z') || (tempName[i] >= 'a' && tempName[i] <= 'z') || tempName[i] == ' ' || tempName[i] == '\0'))
				return WRONG_NAME;
			else
				cardData->cardHolderName[i] = tempName[i];
		return OK_card;
	}
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData) {
	uint8_t tempExpiryDate[50] = "NaN";
	printf("Please Enter the Card Expiry Date in the Format MM/YY: ");
	gets(tempExpiryDate);
	uint16_t len = strlen(tempExpiryDate);
	if (!(len == 5 && tempExpiryDate[0] <= '1' && tempExpiryDate[0] >= '0' && tempExpiryDate[1] >= '0' && tempExpiryDate[1] <= '9' &&
		tempExpiryDate[2] == '/' && tempExpiryDate[3] >= '0' && tempExpiryDate[3] <= '9' && tempExpiryDate[4] >= '0' && tempExpiryDate[4] <= '9'))
		return WRONG_EXP_DATE;
	else {
		for (int i = 0; i < len + 1; i++)
			cardData->cardExpirationDate[i] = tempExpiryDate[i];
		return OK_card;
	}
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData) {
	uint8_t tempPAN[50] = "NaN";
	printf("Please Enter the PAN: ");
	gets(tempPAN);
	uint16_t len = strlen(tempPAN);
	if (len < 16 || len > 19)
		return WRONG_PAN;
	else {
		for (int i = 0; i < len + 1; i++) {
			if (!(tempPAN[i] >= '0' && tempPAN[i] <= '9' || tempPAN[i] == '\0'))
				return WRONG_PAN;
			else
				cardData->primaryAccountNumber[i] = tempPAN[i];
		}


		return OK_card;
	}
}