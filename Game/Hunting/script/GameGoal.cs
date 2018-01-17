using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class GameGoal : MonoBehaviour {

    // 0-horse 1-stag 2-hare
    public int[] goal;
    public Text[] goalText;

    public GameObject CanvasRankBoard;
    public GameObject rankResister;
    public GameObject InputField;
    public GameObject rankBoard;
    public rank rankTable;
    public Text clearTimeText;
    public Text rankBoardTextID;
    public Text rankBoardTextTime;
    private bool rankboardOn;
    private bool gameEnd;

    public int sumGoal;
    private string id;
    private float time;

    [SerializeField]
    private string BASE_URL = "https://docs.google.com/forms/d/e/1FAIpQLSfNtauu23wSJV1uUv3jYFqtz_7St5_sYtoOW8LQe8xnXyUbhQ/formResponse";

    static GameGoal gameGoalInstance;

    public static GameGoal Instance()
    {
        return gameGoalInstance;
    }

    // Use this for initialization
    void Start () {
        gameEnd = false;
        rankboardOn = false;
        time = 0;
        gameGoalInstance = this;

        rankboardOn = false;

        for (int i = 0; i < goal.Length; i++)
        {
            goal[i] = Random.Range(1, 3);
            /*
            if (i == 1)
                goal[i] = 1;
                */
            goalText[i].text = goal[i].ToString();
            sumGoal += goal[i];
        }
    }
	
	// Update is called once per frame
	void Update () {
        CheckEndGame();

        if(rankboardOn)
            if(Input.GetKeyDown(KeyCode.Escape))
                Application.Quit();
    }

    void CheckEndGame()
    {
        if (sumGoal == 0 && gameEnd == false)
        {
            Debug.Log("game end");
            CanvasRankBoard.SetActive(true);
            clearTimeText.text += time.ToString("N1") + "s";
            Cursor.lockState = CursorLockMode.None;
            Cursor.visible = true;
            gameEnd = true;
        }
        else if (sumGoal != 0)
            time += Time.deltaTime;

        for (int i = 0; i < goal.Length; i++)
            goalText[i].text = goal[i].ToString();
    }

    public void Quit()
    {
        SceneManager.LoadScene(0);
    }

    public void Regist()
    {
        InputField.SetActive(true);
    }

    IEnumerator Post(string ID)
    {
        WWWForm form = new WWWForm();
        form.AddField("entry.1541889969", id);
        form.AddField("entry.1522074914", time.ToString("N1"));
        byte[] rawData = form.data;
        WWW www = new WWW(BASE_URL, rawData);
        yield return www;
    }
    public void EndInput()
    {
        id = InputField.GetComponent<InputField>().text;
        Debug.Log(id);

        // id 입력, 데이터 전송
        StartCoroutine(Post(id));

        // 랭킹보드 출력
        rankBoard.SetActive(true);
        rankResister.SetActive(false);
        LoadRank();
    }
    public void LoadRank()
    {
        for (int i = 0; i < rankTable.dataArray.Length; i++)
        {
            rankBoardTextID.text += rankTable.dataArray[i].ID + "\n";
            rankBoardTextTime.text += rankTable.dataArray[i].TIME + "\n";
            //Debug.Log(rankTable.dataArray[i].ID + "    " + rankTable.dataArray[i].TIME);
        }
        rankboardOn = true;
    }
}
