/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../SerialTerminal/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[28];
    char stringdata[549];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 14), // "openSerialPort"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 15), // "closeSerialPort"
QT_MOC_LITERAL(4, 43, 5), // "about"
QT_MOC_LITERAL(5, 49, 9), // "writeData"
QT_MOC_LITERAL(6, 59, 4), // "data"
QT_MOC_LITERAL(7, 64, 8), // "readData"
QT_MOC_LITERAL(8, 73, 12), // "writeDataTwo"
QT_MOC_LITERAL(9, 86, 11), // "readDataTwo"
QT_MOC_LITERAL(10, 98, 11), // "handleError"
QT_MOC_LITERAL(11, 110, 28), // "QSerialPort::SerialPortError"
QT_MOC_LITERAL(12, 139, 5), // "error"
QT_MOC_LITERAL(13, 145, 14), // "handleErrorTwo"
QT_MOC_LITERAL(14, 160, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(15, 182, 31), // "on_horizontalSlider_sliderMoved"
QT_MOC_LITERAL(16, 214, 8), // "position"
QT_MOC_LITERAL(17, 223, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(18, 247, 34), // "on_horizontalSlider_sliderRel..."
QT_MOC_LITERAL(19, 282, 23), // "on_pushButton_3_clicked"
QT_MOC_LITERAL(20, 306, 27), // "on_actionConnect2_triggered"
QT_MOC_LITERAL(21, 334, 30), // "on_actionDisconnect2_triggered"
QT_MOC_LITERAL(22, 365, 33), // "on_horizontalSlider_3_sliderM..."
QT_MOC_LITERAL(23, 399, 36), // "on_horizontalSlider_3_sliderR..."
QT_MOC_LITERAL(24, 436, 34), // "on_horizontalSlider_3_valueCh..."
QT_MOC_LITERAL(25, 471, 5), // "value"
QT_MOC_LITERAL(26, 477, 36), // "on_horizontalSlider_4_sliderR..."
QT_MOC_LITERAL(27, 514, 34) // "on_horizontalSlider_4_valueCh..."

    },
    "MainWindow\0openSerialPort\0\0closeSerialPort\0"
    "about\0writeData\0data\0readData\0"
    "writeDataTwo\0readDataTwo\0handleError\0"
    "QSerialPort::SerialPortError\0error\0"
    "handleErrorTwo\0on_pushButton_clicked\0"
    "on_horizontalSlider_sliderMoved\0"
    "position\0on_pushButton_2_clicked\0"
    "on_horizontalSlider_sliderReleased\0"
    "on_pushButton_3_clicked\0"
    "on_actionConnect2_triggered\0"
    "on_actionDisconnect2_triggered\0"
    "on_horizontalSlider_3_sliderMoved\0"
    "on_horizontalSlider_3_sliderReleased\0"
    "on_horizontalSlider_3_valueChanged\0"
    "value\0on_horizontalSlider_4_sliderReleased\0"
    "on_horizontalSlider_4_valueChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      21,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  119,    2, 0x08 /* Private */,
       3,    0,  120,    2, 0x08 /* Private */,
       4,    0,  121,    2, 0x08 /* Private */,
       5,    1,  122,    2, 0x08 /* Private */,
       7,    0,  125,    2, 0x08 /* Private */,
       8,    1,  126,    2, 0x08 /* Private */,
       9,    0,  129,    2, 0x08 /* Private */,
      10,    1,  130,    2, 0x08 /* Private */,
      13,    1,  133,    2, 0x08 /* Private */,
      14,    0,  136,    2, 0x08 /* Private */,
      15,    1,  137,    2, 0x08 /* Private */,
      17,    0,  140,    2, 0x08 /* Private */,
      18,    0,  141,    2, 0x08 /* Private */,
      19,    0,  142,    2, 0x08 /* Private */,
      20,    0,  143,    2, 0x08 /* Private */,
      21,    0,  144,    2, 0x08 /* Private */,
      22,    1,  145,    2, 0x08 /* Private */,
      23,    0,  148,    2, 0x08 /* Private */,
      24,    1,  149,    2, 0x08 /* Private */,
      26,    0,  152,    2, 0x08 /* Private */,
      27,    1,  153,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    6,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   25,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   25,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->openSerialPort(); break;
        case 1: _t->closeSerialPort(); break;
        case 2: _t->about(); break;
        case 3: _t->writeData((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 4: _t->readData(); break;
        case 5: _t->writeDataTwo((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 6: _t->readDataTwo(); break;
        case 7: _t->handleError((*reinterpret_cast< QSerialPort::SerialPortError(*)>(_a[1]))); break;
        case 8: _t->handleErrorTwo((*reinterpret_cast< QSerialPort::SerialPortError(*)>(_a[1]))); break;
        case 9: _t->on_pushButton_clicked(); break;
        case 10: _t->on_horizontalSlider_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->on_pushButton_2_clicked(); break;
        case 12: _t->on_horizontalSlider_sliderReleased(); break;
        case 13: _t->on_pushButton_3_clicked(); break;
        case 14: _t->on_actionConnect2_triggered(); break;
        case 15: _t->on_actionDisconnect2_triggered(); break;
        case 16: _t->on_horizontalSlider_3_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->on_horizontalSlider_3_sliderReleased(); break;
        case 18: _t->on_horizontalSlider_3_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: _t->on_horizontalSlider_4_sliderReleased(); break;
        case 20: _t->on_horizontalSlider_4_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 21)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 21;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
