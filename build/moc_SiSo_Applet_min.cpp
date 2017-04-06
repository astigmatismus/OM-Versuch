/****************************************************************************
** Meta object code from reading C++ file 'SiSo_Applet_min.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/SiSo_Applet_min.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SiSo_Applet_min.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SiSo_AppletMin_t {
    QByteArrayData data[5];
    char stringdata0[46];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SiSo_AppletMin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SiSo_AppletMin_t qt_meta_stringdata_SiSo_AppletMin = {
    {
QT_MOC_LITERAL(0, 0, 14), // "SiSo_AppletMin"
QT_MOC_LITERAL(1, 15, 6), // "Update"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 3), // "frm"
QT_MOC_LITERAL(4, 27, 18) // "slotCalcMonitoring"

    },
    "SiSo_AppletMin\0Update\0\0frm\0"
    "slotCalcMonitoring"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SiSo_AppletMin[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x09 /* Protected */,
       4,    0,   27,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,

       0        // eod
};

void SiSo_AppletMin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SiSo_AppletMin *_t = static_cast<SiSo_AppletMin *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Update((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->slotCalcMonitoring(); break;
        default: ;
        }
    }
}

const QMetaObject SiSo_AppletMin::staticMetaObject = {
    { &SiSo_AppletIF::staticMetaObject, qt_meta_stringdata_SiSo_AppletMin.data,
      qt_meta_data_SiSo_AppletMin,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SiSo_AppletMin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SiSo_AppletMin::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SiSo_AppletMin.stringdata0))
        return static_cast<void*>(const_cast< SiSo_AppletMin*>(this));
    return SiSo_AppletIF::qt_metacast(_clname);
}

int SiSo_AppletMin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SiSo_AppletIF::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
