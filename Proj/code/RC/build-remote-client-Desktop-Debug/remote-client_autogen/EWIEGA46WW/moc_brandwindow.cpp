/****************************************************************************
** Meta object code from reading C++ file 'brandwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "brandwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'brandwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_BrandWindow_t {
    QByteArrayData data[15];
    char stringdata0[272];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BrandWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BrandWindow_t qt_meta_stringdata_BrandWindow = {
    {
QT_MOC_LITERAL(0, 0, 11), // "BrandWindow"
QT_MOC_LITERAL(1, 12, 12), // "home_pressed"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 20), // "on_logoutBtn_pressed"
QT_MOC_LITERAL(4, 47, 20), // "on_goBackBtn_pressed"
QT_MOC_LITERAL(5, 68, 20), // "on_rentedBtn_pressed"
QT_MOC_LITERAL(6, 89, 29), // "on_stationsComboBox_activated"
QT_MOC_LITERAL(7, 119, 5), // "index"
QT_MOC_LITERAL(8, 125, 22), // "on_goBackBtn_2_pressed"
QT_MOC_LITERAL(9, 148, 20), // "on_toRentBtn_pressed"
QT_MOC_LITERAL(10, 169, 31), // "on_stationsComboBox_2_activated"
QT_MOC_LITERAL(11, 201, 25), // "on_calendarWidget_clicked"
QT_MOC_LITERAL(12, 227, 4), // "date"
QT_MOC_LITERAL(13, 232, 20), // "on_uploadBtn_pressed"
QT_MOC_LITERAL(14, 253, 18) // "on_rentBtn_pressed"

    },
    "BrandWindow\0home_pressed\0\0"
    "on_logoutBtn_pressed\0on_goBackBtn_pressed\0"
    "on_rentedBtn_pressed\0on_stationsComboBox_activated\0"
    "index\0on_goBackBtn_2_pressed\0"
    "on_toRentBtn_pressed\0"
    "on_stationsComboBox_2_activated\0"
    "on_calendarWidget_clicked\0date\0"
    "on_uploadBtn_pressed\0on_rentBtn_pressed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BrandWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   70,    2, 0x08 /* Private */,
       4,    0,   71,    2, 0x08 /* Private */,
       5,    0,   72,    2, 0x08 /* Private */,
       6,    1,   73,    2, 0x08 /* Private */,
       8,    0,   76,    2, 0x08 /* Private */,
       9,    0,   77,    2, 0x08 /* Private */,
      10,    1,   78,    2, 0x08 /* Private */,
      11,    1,   81,    2, 0x08 /* Private */,
      13,    0,   84,    2, 0x08 /* Private */,
      14,    0,   85,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::QDate,   12,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void BrandWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BrandWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->home_pressed(); break;
        case 1: _t->on_logoutBtn_pressed(); break;
        case 2: _t->on_goBackBtn_pressed(); break;
        case 3: _t->on_rentedBtn_pressed(); break;
        case 4: _t->on_stationsComboBox_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->on_goBackBtn_2_pressed(); break;
        case 6: _t->on_toRentBtn_pressed(); break;
        case 7: _t->on_stationsComboBox_2_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_calendarWidget_clicked((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 9: _t->on_uploadBtn_pressed(); break;
        case 10: _t->on_rentBtn_pressed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (BrandWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BrandWindow::home_pressed)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject BrandWindow::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_BrandWindow.data,
    qt_meta_data_BrandWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *BrandWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BrandWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BrandWindow.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int BrandWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void BrandWindow::home_pressed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
