/****************************************************************************
** Meta object code from reading C++ file 'recorddlg.h'
**
** Created: Sun Jun 7 19:02:10 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../recorddlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'recorddlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RecordDlg[] = {

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
      11,   10,   10,   10, 0x08,
      33,   10,   10,   10, 0x08,
      70,   58,   10,   10, 0x08,
     124,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_RecordDlg[] = {
    "RecordDlg\0\0OnBtnSettingClicked()\0"
    "OnBtnStopRecordClicked()\0item,column\0"
    "OnTrRecordListItemDoubleClicked(QTreeWidgetItem*,int)\0"
    "TestSoundFinished()\0"
};

void RecordDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        RecordDlg *_t = static_cast<RecordDlg *>(_o);
        switch (_id) {
        case 0: _t->OnBtnSettingClicked(); break;
        case 1: _t->OnBtnStopRecordClicked(); break;
        case 2: _t->OnTrRecordListItemDoubleClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->TestSoundFinished(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData RecordDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject RecordDlg::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_RecordDlg,
      qt_meta_data_RecordDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RecordDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RecordDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RecordDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RecordDlg))
        return static_cast<void*>(const_cast< RecordDlg*>(this));
    return QFrame::qt_metacast(_clname);
}

int RecordDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
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
