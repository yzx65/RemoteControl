/****************************************************************************
** Meta object code from reading C++ file 'AppInfoDlg.h'
**
** Created: Thu Apr 2 16:13:28 2015
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../AppInfoDlg.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AppInfoDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AppInfoThread[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      21,   15,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      43,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_AppInfoThread[] = {
    "AppInfoThread\0\0pq,pw\0emitParser(uint,uint)\0"
    "Init()\0"
};

void AppInfoThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AppInfoThread *_t = static_cast<AppInfoThread *>(_o);
        switch (_id) {
        case 0: _t->emitParser((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        case 1: _t->Init(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData AppInfoThread::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AppInfoThread::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_AppInfoThread,
      qt_meta_data_AppInfoThread, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AppInfoThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AppInfoThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AppInfoThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AppInfoThread))
        return static_cast<void*>(const_cast< AppInfoThread*>(this));
    return QObject::qt_metacast(_clname);
}

int AppInfoThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void AppInfoThread::emitParser(unsigned int _t1, unsigned int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
static const uint qt_meta_data_AppInfoDlg[] = {

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
      12,   11,   11,   11, 0x05,
      29,   11,   11,   11, 0x05,
      45,   11,   11,   11, 0x05,
      62,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      91,   69,   11,   11, 0x0a,
     117,  112,   11,   11, 0x08,
     169,  163,   11,   11, 0x08,
     226,  220,   11,   11, 0x08,
     265,  220,   11,   11, 0x08,
     320,  308,   11,   11, 0x08,
     367,  308,   11,   11, 0x08,
     413,   11,   11,   11, 0x08,
     439,  435,   11,   11, 0x08,
     459,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_AppInfoDlg[] = {
    "AppInfoDlg\0\0emitGetAppData()\0"
    "emitCleanData()\0emitExportData()\0"
    "Init()\0qqParser,weixinParser\0"
    "GetParser(uint,uint)\0item\0"
    "OnLstApplicationItemClicked(QListWidgetItem*)\0"
    "item,\0OnTrWeixinFriendsItemClicked(QTreeWidgetItem*,int)\0"
    "index\0OnCmbQQAccountCurrentIndexChanged(int)\0"
    "OnCmbWeixinAccountCurrentIndexChanged(int)\0"
    "item,column\0OnTrQQFriendsItemClicked(QTreeWidgetItem*,int)\0"
    "OnTrQQTroopsItemClicked(QTreeWidgetItem*,int)\0"
    "OnBtnRefreshClicked()\0url\0OnLinkClicked(QUrl)\0"
    "OnBtnCleanClicked()\0"
};

void AppInfoDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AppInfoDlg *_t = static_cast<AppInfoDlg *>(_o);
        switch (_id) {
        case 0: _t->emitGetAppData(); break;
        case 1: _t->emitCleanData(); break;
        case 2: _t->emitExportData(); break;
        case 3: _t->Init(); break;
        case 4: _t->GetParser((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< uint(*)>(_a[2]))); break;
        case 5: _t->OnLstApplicationItemClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 6: _t->OnTrWeixinFriendsItemClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->OnCmbQQAccountCurrentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->OnCmbWeixinAccountCurrentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->OnTrQQFriendsItemClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 10: _t->OnTrQQTroopsItemClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 11: _t->OnBtnRefreshClicked(); break;
        case 12: _t->OnLinkClicked((*reinterpret_cast< const QUrl(*)>(_a[1]))); break;
        case 13: _t->OnBtnCleanClicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData AppInfoDlg::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AppInfoDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_AppInfoDlg,
      qt_meta_data_AppInfoDlg, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AppInfoDlg::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AppInfoDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AppInfoDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AppInfoDlg))
        return static_cast<void*>(const_cast< AppInfoDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int AppInfoDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void AppInfoDlg::emitGetAppData()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void AppInfoDlg::emitCleanData()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void AppInfoDlg::emitExportData()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void AppInfoDlg::Init()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
QT_END_MOC_NAMESPACE
