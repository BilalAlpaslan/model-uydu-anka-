import csv

veri = []
with open("ornek.csv", "r", newline="") as f:
    reader = csv.reader(f)
    for row in reader:
        veri.append(row)
x = len(veri)
ilk=str(veri[0])
son=str(veri[x-1])

ilk= ilk.replace("[","")
ilk= ilk.replace("]","")
ilk= ilk.replace("\"","")
ilk= ilk.replace("\\","")
ilk= ilk.replace("r","")
ilk= ilk.replace("n","")
ilk= ilk.replace("\'","")
ilklist = ilk.split(",")

son= son.replace("[","")
son= son.replace("]","")
son= son.replace("\"","")
son= son.replace("\\","")
son= son.replace("r","")
son= son.replace("n","")
son= son.replace("\'","")
sonlist = son.split(",")
# ----------------------------------------------------------- #

x= abs(float(ilklist[4]) - float(sonlist[4]))
t= abs(float(sonlist[1]))
v = x/t
#print("hız : "+ str(v))
p = float(sonlist[5])
mg = 3.50
cd =𝑚𝑔*2 / (p * v**2 * t)

#print("cd : "+str(cd))

with open("cd.csv", "a", newline="") as f:
    yazici = csv.writer(f)
    yazici.writerow([v,cd])