/****************************************************************************
** Meta object code from reading C++ file 'FPGA_Interface_Core.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/FPGA_Interface_Core.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FPGA_Interface_Core.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FPGA_IF_Core_t {
    QByteArrayData data[8];
    char stringdata0[93];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FPGA_IF_Core_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FPGA_IF_Core_t qt_meta_stringdata_FPGA_IF_Core = {
    {
QT_MOC_LITERAL(0, 0, 12), // "FPGA_IF_Core"
QT_MOC_LITERAL(1, 13, 12), // "updateCamera"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 15), // "FPGA_IF::camera"
QT_MOC_LITERAL(4, 43, 3), // "cam"
QT_MOC_LITERAL(5, 47, 12), // "updateRefImg"
QT_MOC_LITERAL(6, 60, 9), // "updateGUI"
QT_MOC_LITERAL(7, 70, 22) // "slotUpdateInternalData"

    },
    "FPGA_IF_Core\0updateCamera\0\0FPGA_IF::camera\0"
    "cam\0updateRefImg\0updateGUI\0"
    "slotUpdateInternalData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FPGA_IF_Core[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       5,    0,   37,    2, 0x06 /* Public */,
       6,    0,   38,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   39,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Bool,

       0        // eod
};

void FPGA_IF_Core::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FPGA_IF_Core *_t = static_cast<FPGA_IF_Core *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateCamera((*reinterpret_cast< FPGA_IF::camera(*)>(_a[1]))); break;
        case 1: _t->updateRefImg(); break;
        case 2: _t->updateGUI(); break;
        case 3: { bool _r = _t->slotUpdateInternalData();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (FPGA_IF_Core::*_t)(FPGA_IF::camera );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FPGA_IF_Core::updateCamera)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (FPGA_IF_Core::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FPGA_IF_Core::updateRefImg)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (FPGA_IF_Core::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FPGA_IF_Core::updateGUI)) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject FPGA_IF_Core::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_FPGA_IF_Core.data,
      qt_meta_data_FPGA_IF_Core,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FPGA_IF_Core::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FPGA_IF_Core::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FPGA_IF_Core.stringdata0))
        return static_cast<void*>(const_cast< FPGA_IF_Core*>(this));
    return QObject::qt_metacast(_clname);
}

int FPGA_IF_Core::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void FPGA_IF_Core::updateCamera(FPGA_IF::camera _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FPGA_IF_Core::updateRefImg()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void FPGA_IF_Core::updateGUI()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
