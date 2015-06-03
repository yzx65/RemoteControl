/****************************************************************************
** Meta object code from reading C++ file 'advancemonitordlg.h'
**
** Created: Tue Mar 31 10:16:11 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../advancemonitordlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'advancemonitordlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AdvanceMonitorDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      31,   19,   18,   18, 0x08,
      92,   87,   18,   18, 0x08,
     140,   87,   18,   18, 0x08,
     187,   18,   18,   18, 0x08,
     220,   18,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_AdvanceMonitorDlg[] = {
    "AdvanceMonitorDlg\0\0item,column\0"
    "onTrAdvanceFileMonitorItemClicked(QTreeWidgetItem*,int)\0"
    "item\0onTbUsbPlugRecordItemClicked(QTableWidgetItem*)\0"
    "onTbUsbDirItemDoubleClicked(QTableWidgetItem*)\0"
    "onBtnCleanMonitorRecordClicked()\0"
    "onBtnCancelMonitorClicked()\0"
};

void AdvanceMonitorDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AdvanceMonitorDlg *_t = static_cast<AdvanceMonitorDlg *>(_o);
        switch (_id) {
        case 0: _t->onTrAdvanceFileMonitorItemClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->onTbUsbPlugRecordItemClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 2: _t->onTbUsbDirItemDoubleClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 3: _t->onBtnCleanMonitorRecordClicked(); break;
        case 4: _t->onBtnCancelMonitorClicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData AdvanceMonitorDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AdvanceMonitorDlg::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_AdvanceMonitorDlg,
      qt_meta_data_AdvanceMonitorDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AdvanceMonitorDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AdvanceMonitorDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AdvanceMonitorDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AdvanceMonitorDlg))
        return static_cast<void*>(const_cast< AdvanceMonitorDlg*>(this));
    return QWidget::qt_metacast(_clname);
}

int AdvanceMonitorDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
