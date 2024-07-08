import smtplib
import mysql.connector
from email.mime.text import MIMEText

sender = "dbprojectiut2@gmail.com"
password = "zhpgfyhnwpvphvii"

db = mysql.connector.connect(
    host="localhost",
    user="root",
    password="1283885883Ss",
    database="bank"
)
mysursor = db.cursor()





#********* admin *********#
def add_customer(username , password , first_name , last_name , phone):
    mysursor.callproc("create_customer",(username , password , first_name , last_name , phone),)
    db.commit()

def add_account(account_number , username , active_loan , balance , blocked):
    mysursor.callproc("create_account",(account_number , username , active_loan , balance , blocked),)
    db.commit()

def block_account(acc_num):
    print(mysursor.callproc("block_account" , (acc_num , 0))[1])
    db.commit()

def change_password(username , oldpass , newpass):
    print(mysursor.callproc("change_password" , (username , oldpass , newpass , 0))[3])
    db.commit()

#******** END FUNC ********#

#********* customer *********#
def account_info(Username): 
    db1 = mysql.connector.connect(
    host="localhost",
    user="root",
    password="1283885883Ss",
    database="bank"
    )
    mysursor1 = db1.cursor()
    account_list = []
    mysursor1.execute(f"call account_info('{Username}')")
    for x in mysursor1:
        account_list.append(x)
    return account_list

def send_massage_source(recipients , amount):
    msg = MIMEText(f"Deposit from your card in the amount: {amount}")
    msg['Subject'] = "Transaction"
    msg['From'] = sender
    msg['To'] = ', '.join(recipients)
    with smtplib.SMTP_SSL('smtp.gmail.com', 465) as smtp_server:
       smtp_server.login(sender, password)
       smtp_server.sendmail(sender, recipients, msg.as_string())

def send_massage_dest(recipients , amount):
    msg = MIMEText(f"Deposit to your card in the amount: {amount}")
    msg['Subject'] = "Transaction"
    msg['From'] = sender
    msg['To'] = ', '.join(recipients)
    with smtplib.SMTP_SSL('smtp.gmail.com', 465) as smtp_server:
       smtp_server.login(sender, password)
       smtp_server.sendmail(sender, recipients, msg.as_string())

def send_email(source_account_number, destination_account_number, amount):
    source_number = (mysursor.callproc("find_email" , (source_account_number, 0))[1])
    dest_number = (mysursor.callproc("find_email" , (destination_account_number, 0))[1])
    
    send_massage_source(source_number , amount)
    send_massage_dest(dest_number , amount)

def money_transfer(source_account_number ,
                  destination_account_number,
                  amount):
    ch = mysursor.callproc("money_transfer" , (source_account_number, destination_account_number, amount , 0))[3]
    db.commit()
    if ch:
        send_email(source_account_number, destination_account_number, amount)
        return 1
    else:
        return 0

def N_transaaction(acc_num , nm): 
    db1 = mysql.connector.connect(
    host="localhost",
    user="root",
    password="1283885883Ss",
    database="bank"
    )
    mysursor1 = db1.cursor()
    t_list = []
    mysursor1.execute(f"CALL N_transaction('{acc_num}' , {nm})")
    for x in mysursor1:
        t_list.append(x)
    return t_list

def D_transaaction(acc_num , start_date , end_date): 
    db1 = mysql.connector.connect(
    host="localhost",
    user="root",
    password="1283885883Ss",
    database="bank"
    )
    mysursor1 = db1.cursor()
    t_list = []
    mysursor1.execute(f"CALL get_account_transactions_by_date_range('{acc_num}' , '{start_date}' , '{end_date}')")
    for x in mysursor1:
        t_list.append(x)
    return t_list

def block_account(acc_num):
    args = (acc_num, 0)
    ch = mysursor.callproc("block_account", args)
    db.commit()
    if(ch[1]):
        return 1
    else:
        return 0

#**loan**#

def list_of_loan(username): 
    db1 = mysql.connector.connect(
    host="localhost",
    user="root",
    password="1283885883Ss",
    database="bank"
    )
    mysursor1 = db1.cursor()
    loan_list = []
    mysursor1.execute(f"CALL list_of_loan('{username}')")
    for x in mysursor1:
        loan_list.append(x)
    return loan_list

def List_of_loan_installments(loan_ID): 
    db1 = mysql.connector.connect(
    host="localhost",
    user="root",
    password="1283885883Ss",
    database="bank"
    )
    mysursor1 = db1.cursor()
    installment_list = []
    mysursor1.execute(f"CALL List_of_loan_installments('{loan_ID}')")
    for x in mysursor1:
        installment_list.append(x)
    return installment_list

def loan_amount(acc_num): 
    return mysursor.callproc("loan_amount" , (acc_num , 0))[1]

def ReceiveLoan(acc_num): 
    args = (acc_num, )
    mysursor.callproc(f"ReceiveLoan", args)
    db.commit()

def ReceiveLoan2(acc_num): 
    args = (acc_num, )
    mysursor.callproc(f"ReceiveLoan2", args)
    db.commit()
    
def ReceiveLoan3(acc_num): 
    args = (acc_num, )
    mysursor.callproc(f"ReceiveLoan3", args)
    db.commit()

def Pay_last_installment_loan(loan_ID): 
    ch = mysursor.callproc("Pay_last_installment_loan" , (loan_ID , 0))[1]
    db.commit()
    return ch
