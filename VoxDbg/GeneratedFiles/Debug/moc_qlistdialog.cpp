/****************************************************************************
** Meta object code from reading C++ file 'qlistdialog.h'
**
** Created: Sat May 12 21:04:14 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../qlistdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qlistdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QListDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x08,
      22,   12,   12,   12, 0x08,
      35,   31,   12,   12, 0x08,
      63,   31,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QListDialog[] = {
    "QListDialog\0\0Cancel()\0Select()\0idx\0"
    "OnSelectChange(QModelIndex)\0"
    "OnDoubleClick(QModelIndex)\0"
};

void QListDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QListDialog *_t = static_cast<QListDialog *>(_o);
        switch (_id) {
        case 0: _t->Cancel(); break;
        case 1: _t->Select(); break;
        case 2: _t->OnSelectChange((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 3: _t->OnDoubleClick((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QListDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QListDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_QListDialog,
      qt_meta_data_QListDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QListDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QListDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QListDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QListDialog))
        return static_cast<void*>(const_cast< QListDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int QListDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
