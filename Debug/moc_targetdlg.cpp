/****************************************************************************
** Meta object code from reading C++ file 'targetdlg.h'
**
** Created: Sun Jun 7 18:52:36 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../targetdlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'targetdlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TargetDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      20,   11,   10,   10, 0x05,
      54,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      81,   10,   10,   10, 0x0a,
      94,   10,   10,   10, 0x0a,
     109,   10,   10,   10, 0x0a,
     125,   10,   10,   10, 0x0a,
     153,  147,   10,   10, 0x08,
     174,  147,   10,   10, 0x08,
     205,   10,   10,   10, 0x08,
     242,  230,   10,   10, 0x08,
     293,   10,   10,   10, 0x08,
     317,   10,   10,   10, 0x08,
     337,   10,   10,   10, 0x08,
     363,  358,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_TargetDlg[] = {
    "TargetDlg\0\0pTarget,\0"
    "emitModifyCapturePolicy(uint,int)\0"
    "emitRefreshOnlineLogInfo()\0GetAppData()\0"
    "CleanAppData()\0ExportAppData()\0"
    "ModifyCapturePolicy()\0index\0"
    "DispatchTabInit(int)\0"
    "onCmbLocalDirIndexChanged(int)\0"
    "onToolBarButtonClicked()\0item,column\0"
    "onTrMissionStatusItemClicked(QTreeWidgetItem*,int)\0"
    "onBtnCountinueClicked()\0onBtnPauseClicked()\0"
    "onBtnCancelClicked()\0item\0"
    "onDirDownloadItemClicked(QTableWidgetItem*)\0"
};

void TargetDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TargetDlg *_t = static_cast<TargetDlg *>(_o);
        switch (_id) {
        case 0: _t->emitModifyCapturePolicy((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->emitRefreshOnlineLogInfo(); break;
        case 2: _t->GetAppData(); break;
        case 3: _t->CleanAppData(); break;
        case 4: _t->ExportAppData(); break;
        case 5: _t->ModifyCapturePolicy(); break;
        case 6: _t->DispatchTabInit((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->onCmbLocalDirIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->onToolBarButtonClicked(); break;
        case 9: _t->onTrMissionStatusItemClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 10: _t->onBtnCountinueClicked(); break;
        case 11: _t->onBtnPauseClicked(); break;
        case 12: _t->onBtnCancelClicked(); break;
        case 13: _t->onDirDownloadItemClicked((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData TargetDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TargetDlg::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TargetDlg,
      qt_meta_data_TargetDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TargetDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TargetDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TargetDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TargetDlg))
        return static_cast<void*>(const_cast< TargetDlg*>(this));
    return QWidget::qt_metacast(_clname);
}

int TargetDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void TargetDlg::emitModifyCapturePolicy(unsigned int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TargetDlg::emitRefreshOnlineLogInfo()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
