#kütüphaneler - baslangıç
import sys, serial, serial.tools.list_ports, time
from PyQt5.QtCore import QObject, pyqtSignal, QThread, pyqtSlot , QUrl
from PyQt5.QtWidgets import QApplication, QMainWindow, QWidget, QTextEdit, QListWidget, QListView
from PyQt5.uic import loadUi
from PyQt5.QtWebEngineWidgets import QWebEngineView as QWebView, QWebEnginePage as QWebPage
import csv
#kütüphaneler - son


#port tespit etme - baslangic       #
ports = [
    p.device
    for p in serial.tools.list_ports.comports()
    if 'USB' in p.description
    ]

if not ports:
    raise IOError("Seri Baglantili cihaz yok!")
else:
    ser = serial.Serial("COM5",9600)
#port tespit etme - son              #

# verilerin kaydedileceği listeler ---------
liste_1=[0,0,0,0,0,0]
liste_2=[0,0,0,0,0,0]
liste_3=[0,0,0,0,0,0]
liste_4=[0,0,0,0,0,0]
liste_5=[0,0,0,0,0,0]
liste_6=[0,0,0,0,0,0]
liste_7=[0,0,0,0,0,0]
liste_8=[0,0,0,0,0,0]
liste_9=[0,0,0,0,0,0]
liste_10=[0,0,0,0,0,0]
liste_11=[0,0,0,0,0,0]
liste_12=[0,0,0,0,0,0]
liste_13=[0,0,0,0,0,0]
liste_14=[0,0,0,0,0,0]
liste_y =[0,1,2,3,4]
#-------------------------------------------
liste_line =["","","","","","","","","",""]  #ekrana yazdırılıcak olan bütün değerlerin olduğu kiste


deger = [1]  #yükseklik grafikleri arasında geçiş yapmak için tutulan liste 
# grafikler arası geçiş sistemi   --başlangıç--
def degis(self):
    x=len(deger)
    if deger[x-1]:
        deger.append(0)
    else:
        deger.append(1)
# grafikler arası geçiş sistemi    -- son --


class Worker(QObject):
    finished = pyqtSignal()
    intReady = pyqtSignal(int)

    @pyqtSlot()
    def __init__(self):
        super(Worker, self).__init__()
        self.working = True

    def work(self):
        while self.working:

            # seri portdan gelen bilginin kullamacağınız şekilde düzenlenmesi  --başlangıç--
            line = ser.readline().decode('utf-8')
            tup = line.split(",")
            liste_line.append(line.replace(",","  "))

            index_1=tup[0]
            index_2=tup[1]
            index_3=tup[2]
            index_4=tup[3]
            index_5=tup[4]
            index_6=tup[5]
            index_7=tup[6]
            index_8=tup[7]
            index_9=tup[8]
            index_10=tup[9]
            index_11=tup[10]
            index_12=tup[11]
            index_13=tup[12]
            index_14=tup[13]

            liste_1.append(index_1)
            liste_2.append(index_2)
            liste_3.append(index_3)
            liste_4.append(index_4)
            liste_5.append(index_5)
            liste_6.append(index_6)
            liste_7.append(index_7)
            liste_8.append(index_8)
            liste_9.append(index_9)
            liste_10.append(index_10)
            liste_11.append(index_11)
            liste_12.append(index_12)
            liste_13.append(index_13)
            liste_14.append(index_14)
            # seri portdan gelen bilginin kullamacağınız şekilde düzenlenmesi  -- son --

            # csv kayıt      --başlangıç--
            with open("ornek.csv", "a", newline="") as f:
            	yazici = csv.writer(f)
            	yazici.writerow([tup])
            # csv kayıt        -- son --

            time.sleep(0.05)  # her bir yenilenme için geçen süre
            self.intReady.emit(line)
        self.finished.emit()



class qt(QMainWindow):
    def __init__(self):
        QMainWindow.__init__(self)
        loadUi('deneme.ui', self)  # ui sayfasının yüklenmesi
        self.thread = None
        self.worker = None
        self.label_1.setText("    port: "+ ports[0])

        self.start_loop()
    def start_loop(self):

        self.worker = Worker() 
        self.thread = QThread() 
        self.worker.moveToThread(self.thread) 
        self.thread.started.connect(self.worker.work)

        self.worker.intReady.connect(self.update)
        self.worker.intReady.connect(self.update_animation)
        self.worker.intReady.connect(self.update_gps)

        self.btn_d.clicked.connect(degis)

        self.label_3.setText("3450")

        self.worker.finished.connect(self.thread.quit)  
        self.worker.finished.connect(self.worker.deleteLater) 
        self.thread.finished.connect(self.thread.deleteLater)  
        self.thread.start()




    def update(self):
        y=len(liste_y)
        liste_y.append(y)

        # grafiklerin çizilmesi       --başlangıç--
        y=len(liste_y)
        x=len(liste_7)
        resulty = liste_y[y-5:]
        resultx = liste_7[x-5:]
        self.MplWidget_1.canvas.axes.clear()
        self.MplWidget_1.canvas.axes.plot(resulty,resultx)
        self.MplWidget_1.canvas.axes.set_title('sıcaklık  Celcius')
        self.MplWidget_1.canvas.draw() 

        a = len(deger)
        if deger[a-1]:
            y=len(liste_y)
            x=len(liste_5)
            resulty = liste_y[y-5:]
            resultx = liste_5[x-5:]
            self.MplWidget_2.canvas.axes.clear()
            self.MplWidget_2.canvas.axes.plot(resulty,resultx)
            self.MplWidget_2.canvas.axes.set_title('bmp yükseklik  metre')
            self.MplWidget_2.canvas.draw()
        else:
            y=len(liste_y)
            x=len(liste_14)
            resulty = liste_y[y-5:]
            resultx = liste_14[x-5:]
            self.MplWidget_2.canvas.axes.clear()
            self.MplWidget_2.canvas.axes.plot(resulty,resultx)
            self.MplWidget_2.canvas.axes.set_title('gps yükseklik  metre')
            self.MplWidget_2.canvas.draw()
        
        
        y=len(liste_y)
        x=len(liste_8)
        resulty = liste_y[y-5:]
        resultx = liste_8[x-5:]
        self.MplWidget_3.canvas.axes.clear()
        self.MplWidget_3.canvas.axes.plot(resulty,resultx)
        self.MplWidget_3.canvas.axes.set_title('pil voltaj  volt')
        self.MplWidget_3.canvas.draw() 

        y=len(liste_y)
        x=len(liste_6)
        resulty = liste_y[y-5:]
        resultx = liste_6[x-5:]
        self.MplWidget_4.canvas.axes.clear()
        self.MplWidget_4.canvas.axes.plot(resulty,resultx)
        self.MplWidget_4.canvas.axes.set_title('basınç  Pascal')
        self.MplWidget_4.canvas.draw()

        metins = [self.metin_1,self.metin_2,self.metin_3,self.metin_4,self.metin_5,self.metin_6,self.metin_7,self.metin_8,self.metin_9]
        x=len(liste_line)
        metins[0].setText(liste_line[x-9])
        metins[1].setText(liste_line[x-8])
        metins[2].setText(liste_line[x-7])
        metins[3].setText(liste_line[x-6])
        metins[4].setText(liste_line[x-5])
        metins[5].setText(liste_line[x-4])
        metins[6].setText(liste_line[x-3])
        metins[7].setText(liste_line[x-2])
        metins[8].setText(liste_line[x-1])


    def update_animation(self):
        y=len(liste_y)
        url = f"http://127.0.0.1:8000/anka/"+ str(liste_9[y-1]) +"/"+ str(liste_10[y-1]) +"/"+ str(liste_11[y-1])
        self.dw_2.load(QUrl(url))
        

    def update_gps(self):
        y=len(liste_y)
        if liste_12[y-1]=="0.00":
            self.dw.load(QUrl("http://127.0.0.1:8000/map/40910/29184"))
        else:
            x = int(liste_12[y-1])*1000
            y = int(liste_13[y-1])*1000
            self.dw.load(QUrl("http://127.0.0.1:8000/map/" + str(x) + "/"+ str(y) ))

        # grafiklerin çizilmesi         -- son --
        

def run():
    app = QApplication(sys.argv)
    widget = qt()
    widget.show()
    sys.exit(app.exec_())

if __name__ == "__main__":
    run()





