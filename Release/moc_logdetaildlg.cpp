/****************************************************************************
** Meta object code from reading C++ file 'logdetaildlg.h'
**
** Created: Thu Sep 10 21:18:24 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../logdetaildlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'logdetaildlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LogDetailDlg[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      29,   14,   13,   13, 0x05,
      70,   14,   13,   13, 0x05,
     113,   14,   13,   13, 0x05,
     154,   14,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
     195,   13,   13,   13, 0x08,
     219,   13,   13,   13, 0x08,
     243,   13,   13,   13, 0x08,
     269,   13,   13,   13, 0x08,
     293,   13,   13,   13, 0x08,
     323,  317,   13,   13, 0x08,
     354,  317,   13,   13, 0x08,
     387,  317,   13,   13, 0x08,
     418,  317,   13,   13, 0x08,
     449,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_LogDetailDlg[] = {
    "LogDetailDlg\0\0targetId,table\0"
    "emitLogDetailInfo(uint,PageTableWidget*)\0"
    "emitLogDownloadInfo(uint,PageTableWidget*)\0"
    "emitLogUploadInfo(uint,PageTableWidget*)\0"
    "emitLogPluginInfo(uint,PageTableWidget*)\0"
    "onChkOnlineLogClicked()\0onChkLogDetailClicked()\0"
    "onChkLogDownloadClicked()\0"
    "onChkLogUploadClicked()\0onChkLogPluginClicked()\0"
    "tarId\0onQueryLogDetailFinished(uint)\0"
    "onQueryLogDownloadFinished(uint)\0"
    "onQueryLogUploadFinished(uint)\0"
    "onQueryLogPluginFinished(uint)\0"
    "RefreshOnlineLogInfo()\0"
};

void LogDetailDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LogDetailDlg *_t = static_cast<LogDetailDlg *>(_o);
        switch (_id) {
        case 0: _t->emitLogDetailInfo((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< PageTableWidget*(*)>(_a[2]))); break;
        case 1: _t->emitLogDownloadInfo((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< PageTableWidget*(*)>(_a[2]))); break;
        case 2: _t->emitLogUploadInfo((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< PageTableWidget*(*)>(_a[2]))); break;
        case 3: _t->emitLogPluginInfo((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< PageTableWidget*(*)>(_a[2]))); break;
        case 4: _t->onChkOnlineLogClicked(); break;
        case 5: _t->onChkLogDetailClicked(); break;
        case 6: _t->onChkLogDownloadClicked(); break;
        case 7: _t->onChkLogUploadClicked(); break;
        case 8: _t->onChkLogPluginClicked(); break;
        case 9: _t->onQueryLogDetailFinished((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 10: _t->onQueryLogDownloadFinished((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 11: _t->onQueryLogUploadFinished((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 12: _t->onQueryLogPluginFinished((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 13: _t->RefreshOnlineLogInfo(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData LogDetailDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject LogDetailDlg::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_LogDetailDlg,
      qt_meta_data_LogDetailDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LogDetailDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LogDetailDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LogDetailDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LogDetailDlg))
        return static_cast<void*>(const_cast< LogDetailDlg*>(this));
    return QWidget::qt_metacast(_clname);
}

int LogDetailDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void LogDetailDlg::emitLogDetailInfo(unsigned int _t1, PageTableWidget * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void LogDetailDlg::emitLogDownloadInfo(unsigned int _t1, PageTableWidget * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void LogDetailDlg::emitLogUploadInfo(unsigned int _t1, PageTableWidget * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void LogDetailDlg::emitLogPluginInfo(unsigned int _t1, PageTableWidget * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
