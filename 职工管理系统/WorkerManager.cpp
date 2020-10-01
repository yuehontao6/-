#include"WorkerManager.h"

WorkerManager::WorkerManager() {
	//1.�ļ�������
	ifstream ifs;   //���ڴ��ļ��ж�ȡ����
	ifs.open(FILENAME, ios::in); //���ļ���ȡ���� ����ļ������� ��򿪳���

	if (!ifs.is_open()) { //�򿪳���

		cout << "�ļ�������" << endl;
		//��ʼ������
		//��ʼ����¼����
		m_EmpNum = 0;
		// ��ʼ������ָ��
		m_EmpArray = NULL;
		// ��ʼ���ļ��Ƿ�Ϊ��
		m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//2.�ļ����� ����Ϊ��
	char ch;
	ifs >> ch;


	//�����ļ���ֻ��һ������ ����Ϊ��Ϊ�� 1������ch ���ļ��л�ʣһ���ļ���β�� ��Ϊ��
	if (ifs.eof()) {  
		//�ļ�Ϊ��
		cout << "�ļ�Ϊ�գ�" << endl;
		//��ʼ����¼����
		this->m_EmpNum = 0;
		// ��ʼ������ָ��
		this->m_EmpArray = NULL;
		// ��ʼ���ļ��Ƿ�Ϊ��
		this->m_FileIsEmpty = true;
		ifs.close();
		return;

	}

	//3.�ļ����ڣ����Ҽ�¼����

	int num = this->get_EmpNum();
	//cout << "ְ������Ϊ�� " << num << endl;
	this->m_EmpNum = num; //ͳ��������ֵ��ְ������


     //���ٿռ�
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//���ļ��е����ݴ浽���鵱��
	this->init_Emp();

	/*for (int i = 0; i < this->m_EmpNum; i++) {
		cout << "ְ�����:" << this->m_EmpArray[i]->m_Id
			<< "  ����:" << this->m_EmpArray[i]->m_Name
			<< "  ���ű��:" << this->m_EmpArray[i]->m_DeptId << endl;
	}*/
}


//����ְ�����������ʾ�˵�����
void WorkerManager::Show_Menu() {
	cout << "*************************" << endl;
	cout << "******  ��ӭʹ��ְ������ϵͳ�� *******" << endl;
	cout << "****** 0. �˳�������� ********" << endl;
	cout << "****** 1. ����ְ����Ϣ ********" << endl;
	cout << "****** 2. ��ʾְ����Ϣ ********" << endl;
	cout << "****** 3. ɾ����ְְ����Ϣ ********" << endl;
	cout << "****** 4. �޸�ְ����Ϣ ********" << endl;
	cout << "****** 5. ����ְ����Ϣ ********" << endl;
	cout << "****** 6. ���ձ������ ********" << endl;
	cout << "****** 7. ��������ĵ� ********" << endl;
	cout << "****************************" << endl;
	cout << endl;
}

// �˳�ϵͳ
void WorkerManager::ExitSystem() {
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0); //�˳�����

}

//���ְ��
void WorkerManager::Add_Emp() {
	cout << "���������ְ������:  " << endl;
	int addNum = 0;  //�����û�����������
	cin >> addNum;

	if (addNum > 0) {
		//���
		//��������¿ռ��С
		int newSize = this->m_EmpNum + addNum;  //�¿ռ�����=ԭ����¼����+��������

		//�����¿ռ�
		Worker** newSpace = new Worker * [newSize];

		//��ԭ���ռ������ݣ��������¿ռ���
		if (this->m_EmpArray != NULL) {
			for (int i = 0; i < this->m_EmpNum; i++) {
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//�������������
		for (int i = 0; i < addNum; i++) {
			int id;   //ְ�����
			string name;   // ְ������
			int dSelect;    // ����ѡ��
			
			cout << "������� " << i + 1 << " ����ְ����ţ�" << endl;
			cin >> id;

			cout << "������� " << i + 1 << " ����ְ��������" << endl;
			cin >> name;

			cout << "��ѡ���ְ���ĸ�λ: " << endl;
			cout << "1, ��ְͨ��" << endl;
			cout << "2, ����" << endl;
			cout << "3, �ϰ�" << endl;
			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect) {
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				break;
			}
			//������ְ��ְ�𣬱��浽������
			newSpace[this->m_EmpNum + i] = worker;
		}

		//�ͷ�ԭ�еĿռ�
		delete[] this->m_EmpArray;

		//�����¿ռ��ָ��
		this->m_EmpArray = newSpace;

		//�����µ�ְ������
		this->m_EmpNum = newSize;

		//����ְ����Ϊ�ձ�־
		this->m_FileIsEmpty = false;

		//��ʾ��ӳɹ�
		cout << "��ӳɹ�" << addNum << "����ְ����" << endl;

		//�������ݵ��ļ���
		this->Save();
	}
	else {
		cout << "������������" << endl;
	}

	//������������� �ص��ϼ�Ŀ¼
	system("pause");
	system("cls");
}

//�����ļ�
void WorkerManager::Save() {

	// �ļ����������
	ofstream ofs;
	ofs.open(FILENAME, ios::out); //������ķ�ʽ���ļ�   --д�ļ�

	//��ÿ���˵�����д�뵽�ļ���
	//���ļ��ж�ȡ����  ifs>>
	//���ļ���д������ ofs<<
	for (int i = 0; i < this->m_EmpNum; i++) {  
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}
	//�ر��ļ�
	ofs.close();
}

//ͳ������
int WorkerManager::get_EmpNum() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in); //���ļ����ڶ�ȡ���� ����ļ���������򿪳���

	int id;
	string name;
	int dId;

	int num = 0;

	while (ifs >> id && ifs >> name && ifs >> dId) {  // Ҫ������Ϣ��ȫ��num++
		//��¼����
		num++;

	}
	ifs.close();

	return num;
}
 
// ��ʼ��Ա������
void WorkerManager::init_Emp() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId) {
		Worker* worker = NULL;

		if (dId ==1)   //��ְͨ��
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2) {   //����

			worker = new Manager(id, name, dId);
		}
		else  //�ϰ�
		{
			worker = new Boss(id, name, dId);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}
	//�ر��ļ�
	ifs.close();
}

// ��ʾְ��
void WorkerManager::Show_Emp() {

	// �ж��ļ��Ƿ�Ϊ��
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ��߼�¼Ϊ�գ�" << endl;
	}
	else {
		for (int i = 0; i < m_EmpNum; i++) {

			//���ö�̬���ó���ӿ�
			this->m_EmpArray[i]->showInfo();
		}
	}

	//�������������
	system("pause");
	system("cls");
}



//ɾ��ְ��
void WorkerManager::Del_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else {
      //����ְ�����ɾ��
		cout << "��������Ҫɾ����ְ����ţ�" << endl;
		int id = 0;
		cin >> id;

		int index = this->IsExist(id); //�����Ƿ�������id��Ա�� ������ڷ��������±� ���򷵻�-1 

		if (index != -1) {  //˵��ְ������ ����Ҫɾ��indexλ���ϵ�ְ��

			//����ǰ�� ����
			for (int i = index; i < this->m_EmpNum - 1; i++) {  //m_EmpNum-1  ��Ȼi+1����Խ��

				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;  //���������м�¼����
			this->Save();   //����ͬ�����µ��ļ���

			cout << "ɾ���ɹ���" << endl;
		}
		else {
			cout << "ɾ��ʧ�� δ�ҵ���ְ��" << endl;
		}
	}
	
	// �����������
	  system("pause");
	  system("cls");
}


//�ж�ְ���Ƿ����  ������ڷ���ְ�����������е�λ�ã������ڷ���-1
int WorkerManager::IsExist(int id) {

	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++) {
		if (this->m_EmpArray[i]->m_Id == id) {

			//�ҵ�ְ��
			index = i;
			break;
		}
	}
	return index;
}

// �޸�ְ��
void WorkerManager::Mod_Emp() {

	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ��߼�¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "�������޸ĵ�ְ����ţ�" << endl;
		int id;
		cin >> id;

		int ret=this->IsExist(id);
		if (ret != -1) {

			//���ұ�ŵ�ְ��
			delete this->m_EmpArray[ret];

			int newId = 0; //ְ�����
			string newName = ""; //ְ������
			int dSelect = 0;  //ְ����λ���

			cout << "�鵽��" << id << "��ְ������������ְ���ţ�" << endl;
			cin >> newId;

			cout << "��������ְ��������:" << endl;
			cin >> newName;

			cout << "��������ְ���ĸ�λ:" << endl;
			cout << "1, ��ְͨ��" << endl;
			cout << "2, ����" << endl;
			cout << "3, �ϰ�" << endl;
			cin >> dSelect;

			Worker* worker = NULL;  //����ָ��
			switch (dSelect)
			{
			    case 1:  // ְ��
					worker = new Employee(newId, newName, dSelect);
					break;
				case 2:  //����
					worker = new Manager(newId, newName, dSelect);
					break;
				case 3:  //  �ϰ�
					worker = new Boss(newId, newName, dSelect);
					break;
				default:
					break;
			}

			//��������
			this->m_EmpArray[ret] = worker;

			cout << "�޸ĳɹ���" << endl;

			//���浽�ļ���
			this->Save();
		}
		else
		{
			cout << "�޸�ʧ�ܣ����޴��ˣ�" << endl;
		}
	}
	
	  //  �����������
	  system("pause");
	  system("cls");

}



//����ְ��
void WorkerManager::Find_Emp() {

	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ��߼�¼Ϊ�գ�" << endl;
	}

	else {
		cout << "��������ҵķ�ʽ:" << endl;
		cout << "1.����ְ���ı�Ž��в���" << endl;
		cout << "2.����ְ�����������в���" << endl;

		int select = 0;
		cin >> select;

		if (select == 1) {
			//���ձ�Ų�
			int id;
			cout << "��������ҵ�ְ���ı�ţ�" << endl;
			cin >> id;

			int ret = IsExist(id);
			
			if (ret != -1)
			{
				//�ҵ�ְ��
				cout << "���ҳɹ�����ְ������Ϣ���£�" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "����ʧ�ܣ� ���޴���" << endl;
			}
			
		}
		else if (select == 2) {
			//����������
			string name;
			cout << "��������ҵ�����" << endl;
			cin >> name;

			//�����ж��Ƿ�鵽�ı�־
			bool flag = false;  //Ĭ��δ�ҵ�ְ��

			for (int i = 0; i < this->m_EmpNum; i++) {
				if (this->m_EmpArray[i]->m_Name == name) {
					cout << "���ҳɹ�,ְ�����Ϊ��" << this->m_EmpArray[i]->m_Id
						<< "��ְ����Ϣ����:" << endl;

					flag = true;

					//������ʾ��Ϣ�ӿ�
					this->m_EmpArray[i]->showInfo();
				}
			}
			if (flag == false)
			{
				cout << "����ʧ�ܣ� ���޴���" << endl;
			}
		}
		else
		{
			cout << "����ѡ������" << endl;
		}
	}
	  //�����������
	system("pause");
	system("cls");
}


//����ְ��
void WorkerManager::Sort_Emp() {

	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��ѡ������ķ�ʽ: " << endl;
		cout << "1.����ְ���Ž�������" << endl;
		cout << "2.����ְ���Ž��н���" << endl;

		int select = 0;
		cin >> select;

		//  ѡ������
		for (int i=0; i < this->m_EmpNum; i++) {

			int minOrMax = i;
			for (int j = i + 1; j < this->m_EmpNum; j++)
			{
				if (select == 1)  //������ ��ʱi Ĭ��Ϊmin
				{
					if (this->m_EmpArray[minOrMax]->m_Id > this->m_EmpArray[j]->m_Id)  // ����ı�ǰ��С�򽻻� 
						minOrMax = j;  //�����±�
				}

				else  //���� ��ʱi Ĭ��Ϊmax
				{
					if (this->m_EmpArray[minOrMax]->m_Id < this->m_EmpArray[j]->m_Id) // ����ı�ǰ��Ĵ� �򽻻�
						minOrMax = j;

				}
			}

			//�ж�һ��ʼ�϶�����Сֵ���������ֵ   �ǲ��Ǻ�������ó�����Сֵ�������ֵ ��������򽻻�����
			if (i != minOrMax) { 
				//��������
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
				this->m_EmpArray[minOrMax] = temp;
			}
		}
	}

	cout << "����ɹ��������Ľ��Ϊ:" << endl;
	this->Save(); //�����Ľ���浽�ļ���
	this->Show_Emp();
}


//����ļ�
void WorkerManager::Clean_File() {

	cout << "ȷ����գ�" << endl;
	cout << "1.ȷ��" << endl;
	cout << "2.����" << endl;

	int select = 0;
	cin >> select;

	if (select == 1) {
		//����ļ�
		//// ios::trunc ����ļ������ʹ������ʱ���ԭ��������
		//����ļ����������½����ļ�
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();

		//�ͷ��������
		if (this->m_EmpArray != NULL)
		{ 
			//ɾ��������ÿ��ְ������
			for (int i = 0; i < this->m_EmpNum; i++) {
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}

			//ɾ����������ָ��
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "��ճɹ���" << endl;
	}
	
	system("pause");
	system("cls");
}



WorkerManager::~WorkerManager()
{
	if (this->m_EmpArray != NULL)
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			if (this->m_EmpArray[i] != NULL)
			{
				delete this->m_EmpArray[i];
			}
		}

		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}