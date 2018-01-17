using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameManagerParameter : MonoBehaviour {

    public GameObject[] canvas; // 0-binocular,1-ui , 2-cctv
    public GameObject[] cam; // 0-main , 1-scope , 2~5-cctv , 6-map
    public GameObject[] itemRoot; // 0-weapon . 1-map
    public AudioClip[] BackGroundSound;

    static GameManagerParameter instance;
    public static GameManagerParameter Instance()
    {
        return instance;
    }

	// Use this for initialization
	void Start () {
        Cursor.lockState = CursorLockMode.Locked;
        Cursor.visible = false;
        instance = this;
        OnOffUI("CanvasPlayerUI", true);
	}
	
	// Update is called once per frame
	void Update () {
		
	}

    public void OnOffUI(string Canvas , bool trueOrfalse)
    {
        for(int i=0; i<canvas.Length; i++)
        {
            if (canvas[i].name == Canvas)
                canvas[i].SetActive(trueOrfalse);
            else
                canvas[i].SetActive(!trueOrfalse);
        }
    }
}
