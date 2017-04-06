/****************************************************************************
** Meta object code from reading C++ file 'FPGA_Interfaceiniselectionwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/FPGA_Interfaceiniselectionwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FPGA_Interfaceiniselectionwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FPGA_IFIniSelectionWindow_t {
    QByteArrayData data[8];
    char stringdata0[127];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FPGA_IFIniSelectionWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FPGA_IFIniSelectionWindow_t qt_meta_stringdata_FPGA_IFIniSelectionWindow = {
    {
QT_MOC_LITERAL(0, 0, 25), // "FPGA_IFIniSelectionWindow"
QT_MOC_LITERAL(1, 26, 23), // "slotComboIniFileChanged"
QT_MOC_LITERAL(2, 50, 0), // ""
QT_MOC_LITERAL(3, 51, 5), // "value"
QT_MOC_LITERAL(4, 57, 14), // "slotButtonLoad"
QT_MOC_LITERAL(5, 72, 13), // "slotButtonStd"
QT_MOC_LITERAL(6, 86, 16), // "slotButtonCancel"
QT_MOC_LITERAL(7, 103, 23) // "slotButtonSelectIniFile"

    },
    "FPGA_IFIniSelectionWindow\0"
    "slotComboIniFileChanged\0\0value\0"
    "slotButtonLoad\0slotButtonStd\0"
    "slotButtonCancel\0slotButtonSelectIniFile"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FPGA_IFIniSelectionWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x09 /* Protected */,
       4,    0,   42,    2, 0x09 /* Protected */,
       5,    0,   43,    2, 0x09 /* Protected */,
       6,    0,   44,    2, 0x09 /* Protected */,
       7,    0,   45,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void FPGA_IFIniSelectionWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FPGA_IFIniSelectionWindow *_t = static_cast<FPGA_IFIniSelectionWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotComboIniFileChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->slotButtonLoad(); break;
        case 2: _t->slotButtonStd(); break;
        case 3: _t->slotButtonCancel(); break;
        case 4: _t->slotButtonSelectIniFile(); break;
        default: ;
        }
    }
}

const QMetaObject FPGA_IFIniSelectionWindow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_FPGA_IFIniSelectionWindow.data,
      qt_meta_data_FPGA_IFIniSelectionWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FPGA_IFIniSelectionWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FPGA_IFIniSelectionWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FPGA_IFIniSelectionWindow.stringdata0))
        return static_cast<void*>(const_cast< FPGA_IFIniSelectionWindow*>(this));
    if (!strcmp(_clname, "Ui_FPGA_InterfaceIniSelectionWindow"))
        return static_cast< Ui_FPGA_InterfaceIniSelectionWindow*>(const_cast< FPGA_IFIniSelectionWindow*>(this));
    return QDialog::qt_metacast(_clname);
}

int FPGA_IFIniSelectionWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
