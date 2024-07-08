from PyQt5.QtWidgets import *
from PyQt5 import QtWidgets
from bank import Ui_login
from welcome import Ui_Welcome
from admin import Ui_admin_panel
from utils import *
import hashlib

import mysql.connector
db = mysql.connector.connect(
    host="localhost",
    user="root",
    password="1283885883Ss",
    database="bank"
)
mysursor = db.cursor()

acc_list = []

class prj_login(QMainWindow, Ui_login):
    def __init__(self):
        super().__init__()
        self.window = QMainWindow()
        self.setupUi(self)
        self.show()
        
        # connections
        self.loginbutt.clicked.connect(self.loginfunction)
        
#******Customer catalog*******#
    def table_init(self):
        self.ui.label_5.setWordWrap(True)
        #tableWidget
        self.ui.tableWidget.setColumnWidth(0, 100)
        self.ui.tableWidget.setColumnWidth(1, 80)
        self.ui.tableWidget.setColumnWidth(2, 60)
        self.ui.tableWidget.setColumnWidth(3, 60)
        self.ui.tableWidget.setColumnWidth(4, 50)

        #tableWidget_2
        self.ui.tableWidget_2.setColumnWidth(0, 110)
        self.ui.tableWidget_2.setColumnWidth(1, 110)
        self.ui.tableWidget_2.setColumnWidth(2, 40)
        self.ui.tableWidget_2.setColumnWidth(3, 40)
        self.ui.tableWidget_2.setColumnWidth(4, 40)
        self.ui.tableWidget_2.setColumnWidth(5, 40)
        self.ui.tableWidget_2.setColumnWidth(6, 40)
        self.ui.tableWidget_2.setColumnWidth(7, 70)
        self.ui.tableWidget_2.setColumnWidth(8, 60)

    def money_transfer(self):
        source_account_number = self.ui.cscn.currentText()
        destination_account_number = self.ui.dcn.text()
        amount = self.ui.balance.text()
        x = money_transfer(source_account_number, destination_account_number, amount)
        if(x):
            self.ui.label_5.setStyleSheet("color: white;")
            self.ui.label_5.setText("The transaction was completed successfully!")
        else:
            self.ui.label_5.setStyleSheet("color: red;")
            self.ui.label_5.setText("Something is wrong!!")

    def N_T(self):
        acc_num = self.ui.cAcc_num.currentText()
        n = self.ui.nEditLine.text()
        x = N_transaaction(acc_num, n)

        row = 0
        self.ui.tableWidget_2.setRowCount(len(x))
        for i in x:
            self.ui.tableWidget_2.setItem(row, 0, QtWidgets.QTableWidgetItem(i[0]))
            self.ui.tableWidget_2.setItem(row, 1, QtWidgets.QTableWidgetItem(str(i[1])))
            self.ui.tableWidget_2.setItem(row, 2, QtWidgets.QTableWidgetItem(str(i[2])))
            self.ui.tableWidget_2.setItem(row, 3, QtWidgets.QTableWidgetItem(str(i[3])))
            self.ui.tableWidget_2.setItem(row, 4, QtWidgets.QTableWidgetItem(str(i[4])))
            self.ui.tableWidget_2.setItem(row, 5, QtWidgets.QTableWidgetItem(str(i[5])))
            self.ui.tableWidget_2.setItem(row, 6, QtWidgets.QTableWidgetItem(str(i[6])))
            self.ui.tableWidget_2.setItem(row, 7, QtWidgets.QTableWidgetItem(str(i[7])))
            self.ui.tableWidget_2.setItem(row, 8, QtWidgets.QTableWidgetItem(str(i[8])))
            row = row + 1

    def D_T(self):
        acc_num = self.ui.cAcc_num.currentText()
        sd = self.ui.dateEditLine.text()
        ed = self.ui.dateEditLine_2.text()
        x = D_transaaction(acc_num, sd, ed)

        row = 0
        self.ui.tableWidget_2.setRowCount(len(x))
        for i in x:
            self.ui.tableWidget_2.setItem(row, 0, QtWidgets.QTableWidgetItem(acc_num))
            self.ui.tableWidget_2.setItem(row, 1, QtWidgets.QTableWidgetItem("Unknown"))
            self.ui.tableWidget_2.setItem(row, 2, QtWidgets.QTableWidgetItem(str(i[0])))
            self.ui.tableWidget_2.setItem(row, 3, QtWidgets.QTableWidgetItem(str(i[1])))
            self.ui.tableWidget_2.setItem(row, 4, QtWidgets.QTableWidgetItem(str(i[2])))
            self.ui.tableWidget_2.setItem(row, 5, QtWidgets.QTableWidgetItem(str(i[3])))
            self.ui.tableWidget_2.setItem(row, 6, QtWidgets.QTableWidgetItem(str(i[4])))
            self.ui.tableWidget_2.setItem(row, 7, QtWidgets.QTableWidgetItem(str(i[7])))
            self.ui.tableWidget_2.setItem(row, 8, QtWidgets.QTableWidgetItem(str(i[6])))
            row = row + 1

    def Block_acc(self):
        acc = self.ui.cAcc_num_2.currentText()
        x = block_account(acc)
        if(x):
            self.ui.label_5.setStyleSheet("color: white;")
            self.ui.label_5.setText("The account has been blocked successfully!")
        else:
            self.ui.label_5.setStyleSheet("color: red;")
            self.ui.label_5.setText("Something is wrong!!")

    def customer_show_loans(self):
        user = self.usernamefield.text()
        row = 0
        x = list_of_loan(user)
        self.ui.tableWidget_3.setRowCount(len(x))
        for i in x:
            self.ui.tableWidget_3.setItem(row, 0, QtWidgets.QTableWidgetItem(i[0]))
            self.ui.tableWidget_3.setItem(row, 1, QtWidgets.QTableWidgetItem(i[1]))
            self.ui.tableWidget_3.setItem(row, 2, QtWidgets.QTableWidgetItem(str(i[2])))
            self.ui.tableWidget_3.setItem(row, 3, QtWidgets.QTableWidgetItem(str(i[3])))
            self.ui.tableWidget_3.setItem(row, 4, QtWidgets.QTableWidgetItem(i[4]))
            row = row + 1

    def customer_show_installments(self):
        loan_id = self.ui.loanID.text()
        x = List_of_loan_installments(loan_id)
        row = 0
        self.ui.tableWidget_4.setRowCount(len(x))
        for i in x:
            self.ui.tableWidget_4.setItem(row, 0, QtWidgets.QTableWidgetItem(i[0]))
            self.ui.tableWidget_4.setItem(row, 1, QtWidgets.QTableWidgetItem(str(i[1])))
            self.ui.tableWidget_4.setItem(row, 2, QtWidgets.QTableWidgetItem(str(i[2])))
            self.ui.tableWidget_4.setItem(row, 3, QtWidgets.QTableWidgetItem(str(i[3])))
            self.ui.tableWidget_4.setItem(row, 4, QtWidgets.QTableWidgetItem(str(i[4])))
            self.ui.tableWidget_4.setItem(row, 5, QtWidgets.QTableWidgetItem(str(i[5])))
            self.ui.tableWidget_4.setItem(row, 6, QtWidgets.QTableWidgetItem(str(i[6])))
            row = row + 1

    def loan_amount(self):
        acc = self.ui.cAcc_num_2.currentText()
        x = loan_amount(acc)
        self.ui.label_5.setStyleSheet("color: white;")
        self.ui.label_5.setText(f"The amount of loan you can get is {x}")

    def receive_loan(self): 
        acc_num = self.ui.cAcc_num_2.currentText()
        if(self.ui.comboBox.currentText() == "normal type"):
            ReceiveLoan(acc_num)
            self.ui.label_5.setStyleSheet("color: white;")
            self.ui.label_5.setText("NOTE : This loan consists of 12 monthly installments, and includes an additional 20 Percent interest")
        else:
            if(self.ui.comboBox.currentText() == "loan to by housing"):
                ReceiveLoan2(acc_num)
                self.ui.label_5.setStyleSheet("color: white;")
                self.ui.label_5.setText("NOTE : This loan consists of 7 installments of 3 months and includes 5 Percent interest and its amount is $21000")
            else:
                ReceiveLoan3(acc_num)
                self.ui.label_5.setStyleSheet("color: white;")
                self.ui.label_5.setText("NOTE : This loan does not include additional interest, and it has 12 monthly installments and its amount is about $504")
    


    def payment(self):
        loanID = self.ui.loanID_2.text()
        x = Pay_last_installment_loan(loanID)
        if(x):
            self.ui.label_5.setStyleSheet("color: white;")
            self.ui.label_5.setText("The payment was completed successfully")
        else:
            self.ui.label_5.setStyleSheet("color: red;")
            self.ui.label_5.setText("Something is wrong!")



#******Admin catalog*******#
    def Add_customer(self):
        username = self.ui.usr1.text()
        password = self.ui.pass1.text()
        password = hashlib.sha256(password.encode()).hexdigest()
        first_name = self.ui.fn.text()
        last_name = self.ui.ln.text()
        phone = self.ui.ph.text()
        add_customer(username, password, first_name, last_name, phone)

    def Add_account(self):
        account_number = self.ui.acc_num.text()
        username = self.ui.usr2.text()
        active_loan = 0
        balance = self.ui.balance.text()
        blocked = 0
        add_account(account_number , username , active_loan , balance , blocked)

    def Block_account(self):
        acc_num = self.ui.acc_num_2.text()
        block_account(acc_num)

    def Change_pass(self):
        username = self.ui.usr3_2.text()
        oldpass = self.ui.oldP.text()
        newpass = self.ui.newP.text()  
        newpass = hashlib.sha256(newpass.encode()).hexdigest()
        oldpass = hashlib.sha256(oldpass.encode()).hexdigest()     
        change_password(username , oldpass , newpass)

    def show_loans(self):
        username = self.ui.usr4.text()
        row = 0
        x = list_of_loan(username)
        self.ui.tableWidget.setRowCount(len(x))
        for i in x:
            self.ui.tableWidget.setItem(row, 0, QtWidgets.QTableWidgetItem(i[0]))
            self.ui.tableWidget.setItem(row, 1, QtWidgets.QTableWidgetItem(i[1]))
            self.ui.tableWidget.setItem(row, 2, QtWidgets.QTableWidgetItem(str(i[2])))
            self.ui.tableWidget.setItem(row, 3, QtWidgets.QTableWidgetItem(str(i[3])))
            self.ui.tableWidget.setItem(row, 4, QtWidgets.QTableWidgetItem(i[4]))
            row = row + 1

    def show_installments(self):
        loan_id = self.ui.loanID.text()
        x = List_of_loan_installments(loan_id)
        row = 0
        self.ui.tableWidget_2.setRowCount(len(x))
        for i in x:
            self.ui.tableWidget_2.setItem(row, 0, QtWidgets.QTableWidgetItem(i[0]))
            self.ui.tableWidget_2.setItem(row, 1, QtWidgets.QTableWidgetItem(str(i[1])))
            self.ui.tableWidget_2.setItem(row, 2, QtWidgets.QTableWidgetItem(str(i[2])))
            self.ui.tableWidget_2.setItem(row, 3, QtWidgets.QTableWidgetItem(str(i[3])))
            self.ui.tableWidget_2.setItem(row, 4, QtWidgets.QTableWidgetItem(str(i[4])))
            self.ui.tableWidget_2.setItem(row, 5, QtWidgets.QTableWidgetItem(str(i[5])))
            self.ui.tableWidget_2.setItem(row, 6, QtWidgets.QTableWidgetItem(str(i[6])))
            row = row + 1
#*******End of Admin catalog**********#



    def loginfunction(self): 
        user = self.usernamefield.text()
        password = self.passwordfield.text()
        if(user == "admin" and password == "admin"):
            #self.close()
            self.window = QtWidgets.QMainWindow()
            self.ui = Ui_admin_panel()
            self.ui.setupUi(self.window)
            self.window.show()

            # connections:
            self.ui.AddCustomer.clicked.connect(self.Add_customer)
            self.ui.AddAccount.clicked.connect(self.Add_account)
            self.ui.block_acc.clicked.connect(self.Block_account)
            self.ui.chng.clicked.connect(self.Change_pass)
            self.ui.loanbutt.clicked.connect(self.show_loans)
            self.ui.installmentBut.clicked.connect(self.show_installments)
        else:
            password = hashlib.sha256(password.encode()).hexdigest()
            mysursor.execute(f"SELECT Login('{user}','{password}')")

            if(mysursor.fetchone()[0]):
                #self.close()
                self.window = QtWidgets.QMainWindow()
                self.ui = Ui_Welcome()
                self.ui.setupUi(self.window)
                self.table_init()
                self.window.show()

                x = account_info(user)
                row = 0
                self.ui.tableWidget.setRowCount(len(x))
                for i in x:
                    self.ui.tableWidget.setItem(row, 0, QtWidgets.QTableWidgetItem(i[0]))
                    self.ui.tableWidget.setItem(row, 1, QtWidgets.QTableWidgetItem(str(i[1])))
                    self.ui.tableWidget.setItem(row, 2, QtWidgets.QTableWidgetItem(str(i[2])))
                    self.ui.tableWidget.setItem(row, 3, QtWidgets.QTableWidgetItem(str(i[3])))
                    self.ui.tableWidget.setItem(row, 4, QtWidgets.QTableWidgetItem(str(i[4])))
                    row = row + 1
                    self.ui.cscn.addItem(i[0])
                    self.ui.cAcc_num.addItem(i[0])
                    self.ui.cAcc_num_2.addItem(i[0])
                    

                #connections:
                self.ui.MoneyTransfer.clicked.connect(self.money_transfer)
                self.ui.NTransaction.clicked.connect(self.N_T)
                self.ui.DTransaction.clicked.connect(self.D_T)
                self.ui.MoneyTransfer_4.clicked.connect(self.Block_acc)
                self.ui.pushButton.clicked.connect(self.customer_show_loans)
                self.ui.pushButton_2.clicked.connect(self.customer_show_installments)
                self.ui.pushButton_4.clicked.connect(self.loan_amount)
                self.ui.pushButton_5.clicked.connect(self.payment)
                self.ui.pushButton_3.clicked.connect(self.receive_loan)

            else:
                self.error.setText("Invalid username or password")
        
        


