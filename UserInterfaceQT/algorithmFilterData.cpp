void MainWindow::arrengeStr() {
    QString auxStr = "A\r\n1.52\r\n1.65\r\n1.61\r\n1.57\r\n1.72\r\nB\r\n67.90\r\n65.00\r\n65.40\r\n64.00\r\n67.10\r\nC\r\n241.7\r\n239.9\r\n239.4\r\n241.3\r\n241.6\r\nD\r\n0120\r\n0130\r\n0155\r\n0180\r\n0190\r\n0215\r\n0230\r\n0235\r\n0245\r\n0275\r\nE\r\n1.325\r\n0.9750000000000001\r\n75.0\r\n45.0\r\n249.25\r\n237.75\r\n";
    int bPos = auxStr.indexOf("B");
    int cPos = auxStr.indexOf("C");
    int dPos = auxStr.indexOf("D");
    int ePos = auxStr.indexOf("E");


    int difCB = cPos - bPos;
    int difDC = dPos - cPos;
    int difED = ePos - dPos;

    QString PSValues = auxStr.mid(0,bPos);
    QString TALValues = auxStr.mid(bPos,difCB);
    QString PTVAlues = auxStr.mid(cPos,difDC);
    QString OTValues = auxStr.mid(dPos,difED);
    QString preControlLimits = auxStr.mid(ePos,auxStr.length()-ePos);

    qDebug() << PSValues;
    qDebug() << TALValues;
    qDebug() << PTVAlues;
    qDebug() << OTValues;
    qDebug() << preControlLimits;

    getStringValues(preControlLimits);

}


QStringList MainWindow::getStringValues(QString& str) {
    QStringList  stringValues;
    bool intFlag = false;
    bool strFlag = false;

    QString auxStr = "";

    for (int i = 0; i<str; ++i) {

        if (str[i].isDigit() or str[i] == '.') {
            intFlag = true;
            auxStr += str[i];
            strFlag = true;
        } else {
            intFlag = false;
        }


        if (intFlag == false and strFlag == true) {
            stringValues.append(auxStr);
            auxStr = "";
            strFlag = false;
        }


    }

    qDebug() << stringValues[0] << stringValues[1] << stringValues[2] << stringValues[3] << stringValues[4];
    return stringValues;
}
