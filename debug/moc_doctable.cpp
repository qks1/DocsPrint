/****************************************************************************
** Meta object code from reading C++ file 'doctable.h'
**
** Created: Mon 6. Aug 07:01:23 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../doctable.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'doctable.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DocTable[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x05,
      30,   25,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      93,    9,    9,    9, 0x08,
     106,    9,    9,    9, 0x08,
     128,    9,    9,    9, 0x08,
     143,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_DocTable[] = {
    "DocTable\0\0close_signal()\0,,,,\0"
    "print_preview(QSqlQueryModel*,QString,QString,QString,QString)\0"
    "close_slot()\0checkbox_pressed(int)\0"
    "preview_slot()\0fill_slot(int)\0"
};

void DocTable::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DocTable *_t = static_cast<DocTable *>(_o);
        switch (_id) {
        case 0: _t->close_signal(); break;
        case 1: _t->print_preview((*reinterpret_cast< QSqlQueryModel*(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5]))); break;
        case 2: _t->close_slot(); break;
        case 3: _t->checkbox_pressed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->preview_slot(); break;
        case 5: _t->fill_slot((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DocTable::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DocTable::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_DocTable,
      qt_meta_data_DocTable, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DocTable::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DocTable::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DocTable::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DocTable))
        return static_cast<void*>(const_cast< DocTable*>(this));
    return QWidget::qt_metacast(_clname);
}

int DocTable::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void DocTable::close_signal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void DocTable::print_preview(QSqlQueryModel * _t1, QString _t2, QString _t3, QString _t4, QString _t5)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
