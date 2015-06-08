#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class CMan;
class CWoman;


//行为基类
class CAction
{
    public:
        CAction() { cout << "CAction init." << endl; }
        virtual ~CAction() { cout << "CAction delete." << endl; }
        virtual void ManAction(CMan& oMan) = 0;
        virtual void WomanAction(CWoman& oWomon) = 0;
};


//人的基类
class CPerson
{
    public:
        CPerson() { cout << "CPerson init." << endl; }
        virtual ~CPerson() { cout << "CPerson delete." << endl; }
        virtual void Accept(CAction* oAction) = 0;
};

//男人
class CMan : public CPerson
{
public:
    CMan() { cout << "CMan init." << endl; }
    virtual ~CMan() { cout << "CMan delete." << endl; }
    virtual void Accept(CAction* oAction)
    {
        oAction->ManAction(*this);
    }
};

//女人
class CWoman : public CPerson
{
public:
    CWoman() { cout << "CWoman init." << endl; }
    virtual ~CWoman() { cout << "CWoman delete." << endl; }
    virtual void Accept(CAction* oAction)
    {
        oAction->WomanAction(*this);
    }
};

//成功行为
class CSuccess : public CAction
{
public:
    CSuccess() { cout << "CSuccess init." << endl; }
    virtual ~CSuccess() { cout << "CSuccess delete." << endl; }
    virtual void ManAction(CMan& oMan)
    {
        cout << "男人成功时，背后有一个靠谱的女人。" << endl;
    }

    virtual void WomanAction(CWoman& oWomon)
    {
        cout << "女人成功时，背后有一个不成功的男人。" << endl;
    }
};


//失败行为
class CFailure : public CAction
{
public:
    CFailure() { cout << "CFailure init." << endl; }
    virtual ~CFailure() { cout << "CFailure delete." << endl; }
    virtual void ManAction(CMan& oMan)
    {
        cout << "男人失败时，闷头喝酒，谁也别劝。" << endl;
    }

    virtual void WomanAction(CWoman& oWomon)
    {
        cout << "女人失败时，两眼汪汪，心情不好。" << endl;
    }
};


//恋爱行为
class CLove : public CAction
{
public:
    CLove() { cout << "CLove init." << endl; }
    virtual ~CLove() { cout << "CLove delete." << endl; }
    virtual void ManAction(CMan& oMan)
    {
        cout << "男人恋爱时，凡事不懂也要装懂。" << endl;
    }

    virtual void WomanAction(CWoman& oWomon)
    {
        cout << "女人恋爱时，凡事懂也要装不懂。" << endl;
    }
};


//工作行为
class CWork : public CAction
{
public:
    CWork() { cout << "CWork init." << endl; }
    virtual ~CWork() { cout << "CWork delete." << endl; }

    virtual void ManAction(CMan& oMan)
    {
        cout << "男人工作时，会不细心。" << endl;
    }

    virtual void WomanAction(CWoman& oWomon)
    {
        cout << "女人工作时，会很细心。" << endl;
    }
};


//存储人类对象的类
class ObjectStructure
{
public:
    typedef vector<CPerson*>::iterator personIt;

    void Attach(CPerson* oPerson)
    {
        vecPerson.push_back(oPerson);
    }
    void Detach(CPerson* oPerson)
    {
        personIt it = find(vecPerson.begin(), vecPerson.end(), oPerson);
        if (vecPerson.end() != it)
        {
            swap(*it, vecPerson.back());
            vecPerson.pop_back();
        }        
    }
    void Accept(CAction* oAction)
    {
        for (personIt it = vecPerson.begin(); it != vecPerson.end(); ++it)
        {
            (*it)->Accept(oAction);
        }
    }

    ~ObjectStructure()
    {
        for (personIt it = vecPerson.begin(); it != vecPerson.end(); ++it)
        {
            delete *it;
        }
    }
private:
    vector<CPerson*> vecPerson;
};

int main()
{
    //先初始化人类的几种行为
    CSuccess* oSuccess = new CSuccess;
    CFailure* oFailure = new CFailure;
    CLove* oLove = new CLove;
    CWork* oWork = new CWork;

    //将人类加入人类列表中
    ObjectStructure oObject;
    oObject.Attach(new CMan);
    oObject.Attach(new CWoman);

    //让不同类型的人类展示不同的行为
    oObject.Accept(oSuccess);
    oObject.Accept(oFailure);
    oObject.Accept(oLove);
    oObject.Accept(oWork);

    delete oSuccess;
    delete oFailure;
    delete oLove;
    return 0;
}