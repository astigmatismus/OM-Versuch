/****************************************************************************
** Meta object code from reading C++ file 'SiSo_AppletIF.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/SiSo_AppletIF.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SiSo_AppletIF.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SiSo_AppletIF_t {
    QByteArrayData data[21];
    char stringdata0[245];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SiSo_AppletIF_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SiSo_AppletIF_t qt_meta_stringdata_SiSo_AppletIF = {
    {
QT_MOC_LITERAL(0, 0, 13), // "SiSo_AppletIF"
QT_MOC_LITERAL(1, 14, 14), // "updateLiveGrab"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 7), // "running"
QT_MOC_LITERAL(4, 38, 21), // "updateRingBufferCount"
QT_MOC_LITERAL(5, 60, 6), // "ccount"
QT_MOC_LITERAL(6, 67, 6), // "icount"
QT_MOC_LITERAL(7, 74, 15), // "updateImageView"
QT_MOC_LITERAL(8, 90, 6), // "imgnum"
QT_MOC_LITERAL(9, 97, 19), // "updateMeanImageView"
QT_MOC_LITERAL(10, 117, 12), // "updateGUIFit"
QT_MOC_LITERAL(11, 130, 16), // "updateMonitoring"
QT_MOC_LITERAL(12, 147, 12), // "FPGA_IF_Img*"
QT_MOC_LITERAL(13, 160, 4), // "imgs"
QT_MOC_LITERAL(14, 165, 10), // "timerstart"
QT_MOC_LITERAL(15, 176, 9), // "timerstop"
QT_MOC_LITERAL(16, 186, 6), // "Update"
QT_MOC_LITERAL(17, 193, 3), // "frm"
QT_MOC_LITERAL(18, 197, 18), // "slotCalcMonitoring"
QT_MOC_LITERAL(19, 216, 14), // "slottimerstart"
QT_MOC_LITERAL(20, 231, 13) // "slottimerstop"

    },
    "SiSo_AppletIF\0updateLiveGrab\0\0running\0"
    "updateRingBufferCount\0ccount\0icount\0"
    "updateImageView\0imgnum\0updateMeanImageView\0"
    "updateGUIFit\0updateMonitoring\0"
    "FPGA_IF_Img*\0imgs\0timerstart\0timerstop\0"
    "Update\0frm\0slotCalcMonitoring\0"
    "slottimerstart\0slottimerstop"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SiSo_AppletIF[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,
       4,    2,   82,    2, 0x06 /* Public */,
       7,    1,   87,    2, 0x06 /* Public */,
       9,    0,   90,    2, 0x06 /* Public */,
      10,    1,   91,    2, 0x06 /* Public */,
      11,    1,   94,    2, 0x06 /* Public */,
      14,    0,   97,    2, 0x06 /* Public */,
      15,    0,   98,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      16,    1,   99,    2, 0x09 /* Protected */,
      16,    0,  102,    2, 0x29 /* Protected | MethodCloned */,
      18,    0,  103,    2, 0x09 /* Protected */,
      19,    0,  104,    2, 0x09 /* Protected */,
      20,    0,  105,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Long, QMetaType::Long,    5,    6,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SiSo_AppletIF::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SiSo_AppletIF *_t = static_cast<SiSo_AppletIF *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateLiveGrab((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->updateRingBufferCount((*reinterpret_cast< long(*)>(_a[1])),(*reinterpret_cast< long(*)>(_a[2]))); break;
        case 2: _t->updateImageView((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->updateMeanImageView(); break;
        case 4: _t->updateGUIFit((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->updateMonitoring((*reinterpret_cast< FPGA_IF_Img*(*)>(_a[1]))); break;
        case 6: _t->timerstart(); break;
        case 7: _t->timerstop(); break;
        case 8: _t->Update((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->Update(); break;
        case 10: _t->slotCalcMonitoring(); break;
        case 11: _t->slottimerstart(); break;
        case 12: _t->slottimerstop(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SiSo_AppletIF::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SiSo_AppletIF::updateLiveGrab)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (SiSo_AppletIF::*_t)(long , long );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SiSo_AppletIF::updateRingBufferCount)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (SiSo_AppletIF::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SiSo_AppletIF::updateImageView)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (SiSo_AppletIF::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SiSo_AppletIF::updateMeanImageView)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (SiSo_AppletIF::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SiSo_AppletIF::updateGUIFit)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (SiSo_AppletIF::*_t)(FPGA_IF_Img * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SiSo_AppletIF::updateMonitoring)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (SiSo_AppletIF::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SiSo_AppletIF::timerstart)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (SiSo_AppletIF::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SiSo_AppletIF::timerstop)) {
                *result = 7;
                return;
            }
        }
    }
}

const QMetaObject SiSo_AppletIF::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_SiSo_AppletIF.data,
      qt_meta_data_SiSo_AppletIF,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SiSo_AppletIF::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SiSo_AppletIF::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SiSo_AppletIF.stringdata0))
        return static_cast<void*>(const_cast< SiSo_AppletIF*>(this));
    return QThread::qt_metacast(_clname);
}

int SiSo_AppletIF::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void SiSo_AppletIF::updateLiveGrab(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SiSo_AppletIF::updateRingBufferCount(long _t1, long _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void SiSo_AppletIF::updateImageView(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void SiSo_AppletIF::updateMeanImageView()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void SiSo_AppletIF::updateGUIFit(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void SiSo_AppletIF::updateMonitoring(FPGA_IF_Img * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void SiSo_AppletIF::timerstart()
{
    QMetaObject::activate(this, &staticMetaObject, 6, Q_NULLPTR);
}

// SIGNAL 7
void SiSo_AppletIF::timerstop()
{
    QMetaObject::activate(this, &staticMetaObject, 7, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
