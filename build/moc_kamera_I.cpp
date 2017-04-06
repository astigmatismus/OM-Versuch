/****************************************************************************
** Meta object code from reading C++ file 'kamera_I.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/kamera_I.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'kamera_I.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CKamera_I_t {
    QByteArrayData data[28];
    char stringdata0[281];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CKamera_I_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CKamera_I_t qt_meta_stringdata_CKamera_I = {
    {
QT_MOC_LITERAL(0, 0, 9), // "CKamera_I"
QT_MOC_LITERAL(1, 10, 12), // "updateActive"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 6), // "active"
QT_MOC_LITERAL(4, 31, 11), // "updateBoard"
QT_MOC_LITERAL(5, 43, 14), // "FPGA_IF::board"
QT_MOC_LITERAL(6, 58, 5), // "board"
QT_MOC_LITERAL(7, 64, 10), // "updatePort"
QT_MOC_LITERAL(8, 75, 13), // "FPGA_IF::port"
QT_MOC_LITERAL(9, 89, 4), // "port"
QT_MOC_LITERAL(10, 94, 13), // "updateShutter"
QT_MOC_LITERAL(11, 108, 3), // "min"
QT_MOC_LITERAL(12, 112, 3), // "val"
QT_MOC_LITERAL(13, 116, 3), // "max"
QT_MOC_LITERAL(14, 120, 16), // "updateBrightness"
QT_MOC_LITERAL(15, 137, 12), // "updateOffset"
QT_MOC_LITERAL(16, 150, 12), // "FPGA_IF::tap"
QT_MOC_LITERAL(17, 163, 3), // "tap"
QT_MOC_LITERAL(18, 167, 10), // "updateGain"
QT_MOC_LITERAL(19, 178, 16), // "updateSensorSize"
QT_MOC_LITERAL(20, 195, 6), // "LPoint"
QT_MOC_LITERAL(21, 202, 7), // "size_px"
QT_MOC_LITERAL(22, 210, 6), // "dPoint"
QT_MOC_LITERAL(23, 217, 8), // "dsize_um"
QT_MOC_LITERAL(24, 226, 17), // "updateImageOffset"
QT_MOC_LITERAL(25, 244, 9), // "offset_px"
QT_MOC_LITERAL(26, 254, 10), // "doffset_um"
QT_MOC_LITERAL(27, 265, 15) // "updateImageSize"

    },
    "CKamera_I\0updateActive\0\0active\0"
    "updateBoard\0FPGA_IF::board\0board\0"
    "updatePort\0FPGA_IF::port\0port\0"
    "updateShutter\0min\0val\0max\0updateBrightness\0"
    "updateOffset\0FPGA_IF::tap\0tap\0updateGain\0"
    "updateSensorSize\0LPoint\0size_px\0dPoint\0"
    "dsize_um\0updateImageOffset\0offset_px\0"
    "doffset_um\0updateImageSize"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CKamera_I[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       4,    1,   67,    2, 0x06 /* Public */,
       7,    1,   70,    2, 0x06 /* Public */,
      10,    3,   73,    2, 0x06 /* Public */,
      14,    3,   80,    2, 0x06 /* Public */,
      15,    4,   87,    2, 0x06 /* Public */,
      18,    4,   96,    2, 0x06 /* Public */,
      19,    2,  105,    2, 0x06 /* Public */,
      24,    2,  110,    2, 0x06 /* Public */,
      27,    2,  115,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, QMetaType::Long, QMetaType::Long, QMetaType::Long,   11,   12,   13,
    QMetaType::Void, QMetaType::Long, QMetaType::Long, QMetaType::Long,   11,   12,   13,
    QMetaType::Void, 0x80000000 | 16, QMetaType::Long, QMetaType::Long, QMetaType::Long,   17,   11,   12,   13,
    QMetaType::Void, 0x80000000 | 16, QMetaType::Long, QMetaType::Long, QMetaType::Long,   17,   11,   12,   13,
    QMetaType::Void, 0x80000000 | 20, 0x80000000 | 22,   21,   23,
    QMetaType::Void, 0x80000000 | 20, 0x80000000 | 22,   25,   26,
    QMetaType::Void, 0x80000000 | 20, 0x80000000 | 22,   21,   23,

       0        // eod
};

void CKamera_I::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CKamera_I *_t = static_cast<CKamera_I *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateActive((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->updateBoard((*reinterpret_cast< FPGA_IF::board(*)>(_a[1]))); break;
        case 2: _t->updatePort((*reinterpret_cast< FPGA_IF::port(*)>(_a[1]))); break;
        case 3: _t->updateShutter((*reinterpret_cast< long(*)>(_a[1])),(*reinterpret_cast< long(*)>(_a[2])),(*reinterpret_cast< long(*)>(_a[3]))); break;
        case 4: _t->updateBrightness((*reinterpret_cast< long(*)>(_a[1])),(*reinterpret_cast< long(*)>(_a[2])),(*reinterpret_cast< long(*)>(_a[3]))); break;
        case 5: _t->updateOffset((*reinterpret_cast< FPGA_IF::tap(*)>(_a[1])),(*reinterpret_cast< long(*)>(_a[2])),(*reinterpret_cast< long(*)>(_a[3])),(*reinterpret_cast< long(*)>(_a[4]))); break;
        case 6: _t->updateGain((*reinterpret_cast< FPGA_IF::tap(*)>(_a[1])),(*reinterpret_cast< long(*)>(_a[2])),(*reinterpret_cast< long(*)>(_a[3])),(*reinterpret_cast< long(*)>(_a[4]))); break;
        case 7: _t->updateSensorSize((*reinterpret_cast< LPoint(*)>(_a[1])),(*reinterpret_cast< dPoint(*)>(_a[2]))); break;
        case 8: _t->updateImageOffset((*reinterpret_cast< LPoint(*)>(_a[1])),(*reinterpret_cast< dPoint(*)>(_a[2]))); break;
        case 9: _t->updateImageSize((*reinterpret_cast< LPoint(*)>(_a[1])),(*reinterpret_cast< dPoint(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CKamera_I::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CKamera_I::updateActive)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (CKamera_I::*_t)(FPGA_IF::board );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CKamera_I::updateBoard)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (CKamera_I::*_t)(FPGA_IF::port );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CKamera_I::updatePort)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (CKamera_I::*_t)(long , long , long );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CKamera_I::updateShutter)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (CKamera_I::*_t)(long , long , long );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CKamera_I::updateBrightness)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (CKamera_I::*_t)(FPGA_IF::tap , long , long , long );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CKamera_I::updateOffset)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (CKamera_I::*_t)(FPGA_IF::tap , long , long , long );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CKamera_I::updateGain)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (CKamera_I::*_t)(LPoint , dPoint );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CKamera_I::updateSensorSize)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (CKamera_I::*_t)(LPoint , dPoint );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CKamera_I::updateImageOffset)) {
                *result = 8;
                return;
            }
        }
        {
            typedef void (CKamera_I::*_t)(LPoint , dPoint );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CKamera_I::updateImageSize)) {
                *result = 9;
                return;
            }
        }
    }
}

const QMetaObject CKamera_I::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CKamera_I.data,
      qt_meta_data_CKamera_I,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CKamera_I::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CKamera_I::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CKamera_I.stringdata0))
        return static_cast<void*>(const_cast< CKamera_I*>(this));
    return QObject::qt_metacast(_clname);
}

int CKamera_I::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void CKamera_I::updateActive(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CKamera_I::updateBoard(FPGA_IF::board _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CKamera_I::updatePort(FPGA_IF::port _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void CKamera_I::updateShutter(long _t1, long _t2, long _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void CKamera_I::updateBrightness(long _t1, long _t2, long _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void CKamera_I::updateOffset(FPGA_IF::tap _t1, long _t2, long _t3, long _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void CKamera_I::updateGain(FPGA_IF::tap _t1, long _t2, long _t3, long _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void CKamera_I::updateSensorSize(LPoint _t1, dPoint _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void CKamera_I::updateImageOffset(LPoint _t1, dPoint _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void CKamera_I::updateImageSize(LPoint _t1, dPoint _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}
QT_END_MOC_NAMESPACE
