/****************************************************************************
** Meta object code from reading C++ file 'vclientview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../VClient/vclientview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vclientview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VClientView_t {
    QByteArrayData data[15];
    char stringdata0[205];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VClientView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VClientView_t qt_meta_stringdata_VClientView = {
    {
QT_MOC_LITERAL(0, 0, 11), // "VClientView"
QT_MOC_LITERAL(1, 12, 14), // "showHideDrawer"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 15), // "connectToServer"
QT_MOC_LITERAL(4, 44, 12), // "setConnected"
QT_MOC_LITERAL(5, 57, 15), // "setDisconnected"
QT_MOC_LITERAL(6, 73, 8), // "showData"
QT_MOC_LITERAL(7, 82, 11), // "socketError"
QT_MOC_LITERAL(8, 94, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(9, 123, 6), // "erreur"
QT_MOC_LITERAL(10, 130, 12), // "commandtyped"
QT_MOC_LITERAL(11, 143, 16), // "startScreenShare"
QT_MOC_LITERAL(12, 160, 15), // "stopScreenShare"
QT_MOC_LITERAL(13, 176, 14), // "sendScreenSize"
QT_MOC_LITERAL(14, 191, 13) // "sendDelayTime"

    },
    "VClientView\0showHideDrawer\0\0connectToServer\0"
    "setConnected\0setDisconnected\0showData\0"
    "socketError\0QAbstractSocket::SocketError\0"
    "erreur\0commandtyped\0startScreenShare\0"
    "stopScreenShare\0sendScreenSize\0"
    "sendDelayTime"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VClientView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x08 /* Private */,
       3,    0,   70,    2, 0x08 /* Private */,
       4,    0,   71,    2, 0x08 /* Private */,
       5,    0,   72,    2, 0x08 /* Private */,
       6,    0,   73,    2, 0x08 /* Private */,
       7,    1,   74,    2, 0x08 /* Private */,
      10,    0,   77,    2, 0x08 /* Private */,
      11,    0,   78,    2, 0x08 /* Private */,
      12,    0,   79,    2, 0x08 /* Private */,
      13,    0,   80,    2, 0x08 /* Private */,
      14,    0,   81,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void VClientView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VClientView *_t = static_cast<VClientView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showHideDrawer(); break;
        case 1: _t->connectToServer(); break;
        case 2: _t->setConnected(); break;
        case 3: _t->setDisconnected(); break;
        case 4: _t->showData(); break;
        case 5: _t->socketError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 6: _t->commandtyped(); break;
        case 7: _t->startScreenShare(); break;
        case 8: _t->stopScreenShare(); break;
        case 9: _t->sendScreenSize(); break;
        case 10: _t->sendDelayTime(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    }
}

const QMetaObject VClientView::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_VClientView.data,
      qt_meta_data_VClientView,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *VClientView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VClientView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VClientView.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int VClientView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
