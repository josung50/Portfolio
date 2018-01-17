using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class HP : MonoBehaviour {

    public static int playerHP;
    public static bool isHit;
    public int maxHP;
    public float recoveryTIme;
    private float timer;
    public Text hpText;

    // Use this for initialization
    void Start () {
        playerHP = 100;
	}
	
	// Update is called once per frame
	void Update () {
        hpText.text = "HP : " + playerHP.ToString();
        Recovery();
        Hit();
        Dead();
    }

    void Recovery()
    {
        if (playerHP < maxHP)
        {
            if (timer > recoveryTIme)
            {
                playerHP++;
                timer = 0;
            }
            else
                timer += Time.deltaTime;
        }
    }

    void Hit()
    {
        if (isHit) // 곰에게 맞으면 false로 바뀜.
        {
            Debug.Log("player hit");
            playerHP -= 35;
            isHit = false;
            TPScharacterCtrl.playerAnimator.SetBool("isHit", true);
        }
        else
        {
            TPScharacterCtrl.playerAnimator.SetBool("isHit", false);
        }
    }

    void Dead()
    {
        if (playerHP <= 0)
        {
            TPScharacterCtrl.playerAnimator.SetBool("isDead", true);
        }
    }
}
