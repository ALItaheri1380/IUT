from main import prj_login
from PyQt5.QtWidgets import QApplication
import sys

app = QApplication([sys.argv])
window = prj_login()
sys.exit(app.exec()) 

#'123' or '1'='1'
#123' OR '1'='1 --
#('123','admin\' OR \'1\'=\'1')
#' or 1=1--'