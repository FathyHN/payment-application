#include<stdio.h>
#include<string.h>
#include"server.h"

extern ST_accountsDB_t accDB[255] = {
	39055.92,"2705140449224230",
	1066.75,"6159066530558710",
	96071.24,"9654011260412520",
	83318.56,"9583043416135670",
	87919.39,"9756294639744350",
	51338.45,"7972394224623120",
	6953.26,"1016816103480160",
	35226.35,"4369155328297600",
	85302.24,"3829245724678870",
	20429.47,"4305923801395620",
	78364.47,"4147648758157850",
	38696.64,"8691810952194660",
	40681.10,"4896231324870790",
	50872.78,"4580956402494950",
	23542.05,"7272070438964210",
	33806.21,"9375748372570530",
	50872.78,"4580956402494950",
	97381.19,"7363870522663310",
	14707.83,"7603485749498200",
	33806.21,"9375748372570530"
};

extern ST_transaction transDB[255] = { 0 };

extern uint8_t accIndex = 0;

EN_transStat_t recieveTransactionData(ST_transaction* transData) {
	EN_serverError_t serverError;
	if (isValidAccount(&(transData->cardHolderData)) == ACCOUNT_NOT_FOUND) {
		transData->transState = DECLINED_STOLEN_CARD;
		saveTransaction(transData);
		return DECLINED_STOLEN_CARD;
	}
	else if (isAmountAvailable(&(transData->terminalData)) == LOW_BALANCE) {
		transData->transState = DECLINED_INSUFFECIENT_FUND;
		saveTransaction(transData);
		return DECLINED_INSUFFECIENT_FUND;
	}
	else {
		accDB[accIndex].balance -= transData->terminalData.transAmount;
		transData->transState = APPROVED;
		saveTransaction(transData);
		return APPROVED;
	}

}

EN_serverError_t isValidAccount(ST_cardData_t* cardData) {
	for (accIndex; accIndex <= 254; accIndex++) {
		if (!(strcmp(accDB[accIndex].primaryAccountNumber, cardData->primaryAccountNumber)))
			return OK;
	}
	return ACCOUNT_NOT_FOUND;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData) {
	ST_accountsDB_t* accountsDatabase = &accDB;
	if (termData->transAmount <= accDB[accIndex].balance)
		return OK;
	else
		return LOW_BALANCE;

}

EN_serverError_t saveTransaction(ST_transaction* transData) {
	if (transDB[254].terminalData.maxTransAmount == 0) {
		static uint8_t transSeqNO = 0;
		transDB[transSeqNO].transactionSequenceNumber = transSeqNO;
		transDB[transSeqNO].cardHolderData = transData->cardHolderData;
		transDB[transSeqNO].terminalData = transData->terminalData;
		transDB[transSeqNO].transState = transData->transState;
		transSeqNO++;
		return OK;
	}

	else
		return SAVING_FAILED;
}

EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction* transData) {

}