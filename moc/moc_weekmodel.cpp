/****************************************************************************
** Meta object code from reading C++ file 'weekmodel.h'
**
** Created: Tue 31. Jan 19:55:59 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../weekmodel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'weekmodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_WeekModel[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: signature, parameters, type, tag, flags
      16,   10,   11,   10, 0x02,
      23,   10,   11,   10, 0x02,
      43,   37,   33,   10, 0x02,

       0        // eod
};

static const char qt_meta_stringdata_WeekModel[] = {
    "WeekModel\0\0bool\0save()\0restore()\0int\0"
    "month\0indexOfFirstDay(int)\0"
};

const QMetaObject WeekModel::staticMetaObject = {
    { &QAbstractListModel::staticMetaObject, qt_meta_stringdata_WeekModel,
      qt_meta_data_WeekModel, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &WeekModel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *WeekModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *WeekModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_WeekModel))
        return static_cast<void*>(const_cast< WeekModel*>(this));
    return QAbstractListModel::qt_metacast(_clname);
}

int WeekModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: { bool _r = save();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 1: { bool _r = restore();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 2: { int _r = indexOfFirstDay((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
