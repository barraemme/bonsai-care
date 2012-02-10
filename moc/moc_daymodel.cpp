/****************************************************************************
** Meta object code from reading C++ file 'daymodel.h'
**
** Created: Fri 10. Feb 18:31:07 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../daymodel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'daymodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DayModel[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   10,    9,    9, 0x0a,

 // methods: signature, parameters, type, tag, flags
      42,    9,   34,    9, 0x02,
      56,    9,   52,    9, 0x02,
      71,    9,   52,    9, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_DayModel[] = {
    "DayModel\0\0bonsai\0addSlot(Bonsai*)\0"
    "QString\0dayName()\0int\0weekDayIndex()\0"
    "monthDayIndex()\0"
};

const QMetaObject DayModel::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_DayModel,
      qt_meta_data_DayModel, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DayModel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DayModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DayModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DayModel))
        return static_cast<void*>(const_cast< DayModel*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int DayModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: addSlot((*reinterpret_cast< Bonsai*(*)>(_a[1]))); break;
        case 1: { QString _r = dayName();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = _r; }  break;
        case 2: { int _r = weekDayIndex();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { int _r = monthDayIndex();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
