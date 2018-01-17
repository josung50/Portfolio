using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Inventory : MonoBehaviour {

    //inventory
    public static int cctvEA;
    public static int batteryEA;
    public static int flareGunEA;

    private float timer;
    private bool delay;

    //related UI
    public Text fKeyActivate;
    public Text cctvEAText;
    public Text batteryEAText;
    public Text flaregunEAText;
    public GameObject[] item;

    //related itemState
    public enum GRABITEM
    {
        gun, cctv, flareGun
    };
    public static GRABITEM grabItem;

    //related CCTV
    public Queue<GameObject> cctv = new Queue<GameObject>();

    static Inventory Inventoryinstance;
    public static Inventory InventoryInstance()
    {
        return Inventoryinstance;
    }

    // Use this for initialization
    void Start () {
        flareGunEA = 5;
        batteryEA = 5;
        timer = 1.5f;
        delay = false;
        fKeyActivate.enabled = false;

        cctvEA = 0;
        cctvEAText.text = "4 / 4";
        for (int i = 1; i <= 4; i++)
        {
            cctv.Enqueue(item[i]);
            cctvEA++;
        }

        Inventoryinstance = this;
    }
	
	// Update is called once per frame
	void Update () {
        GetItemDelay();
        UsingItem();
        SwitchItem();
    }

    
    void OnTriggerStay(Collider collisionObject)
    {
        if (collisionObject.gameObject.tag == "cctv")
        {
            fKeyActivate.text = "F키를 눌러 회수";
            fKeyActivate.enabled = true;
            GetItem(collisionObject);
        }
        else if (collisionObject.gameObject.tag == "battery" || collisionObject.gameObject.tag == "flarebullet")
        {
            fKeyActivate.text = "F키를 눌러 줍기";
            fKeyActivate.enabled = true;
            GetItem(collisionObject);
        }
    }
    void OnTriggerExit(Collider collisionObject)
    {
        if (collisionObject.gameObject.tag == "cctv" || collisionObject.gameObject.tag == "battery" || collisionObject.gameObject.tag == "flarebullet")
        {
            fKeyActivate.enabled = false;
        }
    }
    
    // delay가 걸릴 경우 아이템을 줍지 못한다.
    void GetItem(Collider Object)
    {
        if (Input.GetKeyDown(KeyCode.F))
        {
            if (delay == false)
            {
                if (Object.gameObject.tag == "cctv")
                {
                    cctvEA++;
                    cctvEAText.text = cctvEA.ToString() + " / 4";
                    (Object.transform.Find("Swivel").GetComponent("scr_camera_rotate") as MonoBehaviour).enabled = false;
                    Object.gameObject.SetActive(false);
                    Object.tag = Object.gameObject.name;
                    Object.transform.SetParent(GameManagerParameter.Instance().itemRoot[0].transform);
                    Object.transform.localPosition = new Vector3(-0.037f, -0.154f, 0.456f);
                    Object.transform.localEulerAngles = Vector3.zero;
                    cctv.Enqueue(Object.gameObject);

                    GameManagerParameter.Instance().itemRoot[1].transform.Find(Object.name).gameObject.SetActive(false); // map에서 지움

                    if (cctvEA == 1 && TPScharacterCtrl.playerState == TPScharacterCtrl.PLAYERSTATE.itemIdle)
                        cctv.Peek().SetActive(true);
                        
                }
                else if (Object.gameObject.tag == "battery")
                {
                    if (batteryEA < 5)
                    {
                        batteryEA++;
                        batteryEAText.text = batteryEA.ToString() + " / 5";
                    }
                }
                else if (Object.gameObject.tag == "flarebullet")
                {
                    if (flareGunEA < 5)
                    {
                        flareGunEA++;
                        flaregunEAText.text = flareGunEA.ToString() + " / 5";
                    }
                }
                delay = true;
            }
        }
    }
    void GetItemDelay()
    {
        if (delay)
        {
            timer -= Time.deltaTime;
            if (timer <= 0)
            {
                delay = false;
                timer = 1.5f;
            }
        }
    }
    
    void SwitchItem()
    {
        if (Input.GetKeyDown(KeyCode.Alpha1)) // 무기 들기
        {
            item[0].SetActive(true); // 소총
            item[5].SetActive(false); // 조명탄
            TPScharacterCtrl.playerState = TPScharacterCtrl.PLAYERSTATE.gunIdle;
            grabItem = GRABITEM.gun;
            for (int i = 1; i <= 4; i++)
            {
                if (item[i].tag != "cctv")
                    item[i].SetActive(false); // 설치된 cctv 외 끄기
            }
        }
        else if (Input.GetKeyDown(KeyCode.Alpha4))
        {
            item[0].SetActive(false); // 소총
            item[5].SetActive(true); // 조명탄
            TPScharacterCtrl.playerState = TPScharacterCtrl.PLAYERSTATE.gunIdle;
            grabItem = GRABITEM.flareGun;
            for (int i = 1; i <= 4; i++)
                if (item[i].tag != "cctv")
                    item[i].SetActive(false); // 설치된 cctv 외 끄기
        }
        else if (Input.GetKeyDown(KeyCode.Alpha3) && cctvEA >= 1) // CCTV 들기
        {
            if (cctvEA >= 1)
            {
                item[0].SetActive(false);
                item[5].SetActive(false);
                cctv.Peek().SetActive(true);

                TPScharacterCtrl.playerState = TPScharacterCtrl.PLAYERSTATE.itemIdle;
                grabItem = GRABITEM.cctv;
            }
            else
            {
                //fKeyActivate.text = "사용할 수 있는 CCTV가 없습니다.";
            }
        }
        /*
        if (TPScharacterCtrl.playerState == TPScharacterCtrl.PLAYERSTATE.itemIdle)
        {
            if (Input.GetKeyDown(KeyCode.Alpha1)) // 무기 들기
            {
                item[0].SetActive(true); // 소총
                item[5].SetActive(false); // 조명탄
                TPScharacterCtrl.playerState = TPScharacterCtrl.PLAYERSTATE.gunIdle;
                grabItem = GRABITEM.gun;
            }
            else if (Input.GetKeyDown(KeyCode.Alpha4))
            {
                item[0].SetActive(false); // 소총
                item[5].SetActive(true); // 조명탄
                TPScharacterCtrl.playerState = TPScharacterCtrl.PLAYERSTATE.gunIdle;
                grabItem = GRABITEM.;
            }
            for (int i = 1; i <= 4; i++)
            {
                if (item[i].tag != "cctv")
                    item[i].SetActive(false); // 설치된 cctv 외 끄기
            }
        }
        else if (TPScharacterCtrl.playerState == TPScharacterCtrl.PLAYERSTATE.gunIdle)
        {
            if (Input.GetKeyDown(KeyCode.Alpha3) && cctvEA >= 1) // CCTV 들기
            {
                if (cctvEA >= 1)
                {
                    item[0].SetActive(false);
                    cctv.Peek().SetActive(true);

                    TPScharacterCtrl.playerState = TPScharacterCtrl.PLAYERSTATE.itemIdle;
                    grabItem = GRABITEM.cctv;
                }
                else
                {
                    //fKeyActivate.text = "사용할 수 있는 CCTV가 없습니다.";
                }
            }
        }
        */
    }

    void UsingItem()
    {
        // cctv 설치
        if (grabItem == GRABITEM.cctv)
        {
            if (cctv.Count > 0 && delay == false)
            {
                if (Input.GetButton("Fire1"))
                {
                    Debug.Log("UsingItem " + cctv.Peek().tag);
                    cctvEA--;
                    cctvEAText.text = cctvEA.ToString() + " / 4";

                    GameObject temp = cctv.Dequeue();
                    temp.transform.parent = null;
                    temp.transform.position = gameObject.transform.position + new Vector3(0,0.3f,0);
                    temp.transform.eulerAngles = new Vector3(0, gameObject.transform.eulerAngles.y, 0); // 플레이어가 바라보고 있는 방향
                    (temp.transform.Find("Swivel").GetComponent("scr_camera_rotate") as MonoBehaviour).enabled = true;

                    // map에 표시
                    GameManagerParameter.Instance().itemRoot[1].transform.Find(temp.name).transform.position = temp.transform.position + new Vector3(0, 900, 0);
                    GameManagerParameter.Instance().itemRoot[1].transform.Find(temp.name).gameObject.SetActive(true);

                    temp.gameObject.tag = "cctv";

                    if(cctv.Count > 0) 
                        cctv.Peek().SetActive(true);

                    delay = true;
                }
            }
        }

        // 플래쉬 라이트 건전지 충전
        {
            if(Input.GetKeyDown(KeyCode.K))
            {
                if (batteryEA >= 1)
                {
                    batteryEA--;
                    batteryEAText.text = batteryEA.ToString() + " / 5";
                    FlashLight.batteryTimer = 0;
                }
            }
        }
    }
}
