/****************************************************************************
** Meta object code from reading C++ file 'day.h'
**
** Created: Fri 10. Feb 18:31:18 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../day.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'day.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Day[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: signature, parameters, type, tag, flags
      13,    4,    5,    4, 0x02,
      23,    4,    5,    4, 0x02,
      39,    4,   35,    4, 0x02,
      56,    4,   35,    4, 0x02,
      69,    4,   35,    4, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_Day[] = {
    "Day\0\0QString\0dayName()\0monthName()\0"
    "int\0dayOfWeekIndex()\0monthIndex()\0"
    "dayIndex()\0"
};

const QMetaObject Day::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Day,
      qt_meta_data_Day, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Day::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Day::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Day::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Day))
        return static_cast<void*>(const_cast< Day*>(this));
    return QObject::qt_metacast(_clname);
}

int Day::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { QString _r = dayName();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 1: { QString _r = monthName();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 2: { int _r = dayOfWeekIndex();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { int _r = monthIndex();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: { int _r = dayIndex();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
