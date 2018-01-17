using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class TPScharacterCtrl : MonoBehaviour {

    public static float mouseSensitivityX;
    public static float mouseSensitivityY;
    public float mouseSensitivityIdleX;
    public float mouseSensitivityIdleY;
    private float moveSpeed;
    public float moveSpeedRun = 6f , moveSpeedWalk = 3f;
    private bool isRun;
    public GameObject eyes;

    private float moveFB, moveLR, rotX, rotY, vertVelocity;
    public float jumpForce = 4f;
    private bool hasJumped = false; // 중력 적용을 피하기 위한 변수

    public float minVertical = -45.0f , maxVertical = 45.0f;
    private CharacterController player;
    public static Animator playerAnimator;
    public AudioSource footStep;

    public enum PLAYERSTATE
    {
        gunIdle, useZoom, useBinoculars, itemIdle, useCCTV, useMap
    };
    public static PLAYERSTATE playerState;

    // Use this for initialization
    void Start () {
        playerState = PLAYERSTATE.gunIdle;
        gameObject.GetComponent<Binoculars>().enabled = false;
        gameObject.GetComponent<Zoom>().enabled = false;
        player = GetComponent<CharacterController>();
        playerAnimator = GetComponent<Animator>();
        playerAnimator.SetBool("isJump", false);
        playerAnimator.SetBool("isRun", false);
    }
	
	// Update is called once per frame
	void Update () {

        ControllPlayerState();

        //run
        if (Input.GetKey(KeyCode.LeftShift))
        {
            isRun = true;
            moveSpeed = moveSpeedRun;
        }
        else // walk
        {
            isRun = false;
            moveSpeed = moveSpeedWalk;
        }

        //move : wasd
        Movement();

        //jump : space
        if (Input.GetButtonDown("Jump"))
        {
            playerAnimator.SetBool("isJump", true);
            hasJumped = true;
        }
        ApplyGrvaity();
    }

    void Movement()
    {
        //get input from WASD with walk
        moveFB = Input.GetAxis("Vertical") * moveSpeed;
        moveLR = Input.GetAxis("Horizontal") * moveSpeed;

        if (playerAnimator.GetBool("isBin") == false || playerAnimator.GetBool("isZoom") == false)
        {
            if (playerAnimator.GetBool("isIdle(item)") == false)
            {
                if (moveFB != 0 || moveLR != 0)
                {
                    footStep.enabled = true;
                    if (isRun)
                    {
                        footStep.pitch = 1.3f;
                        footStep.loop = true;
                        playerAnimator.SetBool("isRun", true);
                        playerAnimator.SetBool("isWalk", false);
                    }
                    else
                    {
                        footStep.pitch = 0.6f;
                        footStep.loop = true;
                        playerAnimator.SetBool("isWalk", true);
                        playerAnimator.SetBool("isRun", false);
                    }
                }
                else
                {
                    footStep.enabled = false;
                    playerAnimator.SetBool("isWalk", false);
                    playerAnimator.SetBool("isRun", false);
                }
            }

            else
            {
                if (moveFB != 0 || moveLR != 0)
                    playerAnimator.SetBool("isRun(item)", true);
                else
                    playerAnimator.SetBool("isRun(item)", false);
            }
        }

        //get input from mouse
        rotX = Input.GetAxis("Mouse X") * mouseSensitivityX;
        rotY -= Input.GetAxis("Mouse Y") * mouseSensitivityY; // 마우스 반전 때문에 -값을 취해주는 것
        rotY = Mathf.Clamp(rotY, minVertical, maxVertical); // 수직 앵글의 범위 제한

        //control the movement of the character controller
        Vector3 movement = new Vector3(moveLR, vertVelocity, moveFB);

        //rotate the player (캐릭터가 y축으로만 돌아간다... 좌우 - 앞을 보는 방향의 변화)
        transform.Rotate(0,rotX,0);

        //fix the orientation
        movement = transform.rotation * movement;

        //rotate the camera on the Y axis , 카메라가 위 아래로 돌아간다. X축 회전
        eyes.transform.localRotation = Quaternion.Euler(rotY, 0, 0);

        //move the player
        player.Move(movement * Time.deltaTime);
    }

    private void Jump()
    {
        hasJumped = true;
        print("has jumped");
    }

    private void ApplyGrvaity()
    {
        if (player.isGrounded == true)
        {
            if (hasJumped == false)
            {
                vertVelocity = Physics.gravity.y;
            }
            else
            {
                vertVelocity = jumpForce;
            }
        }
        else
        {
            vertVelocity += Physics.gravity.y * Time.deltaTime;
            vertVelocity = Mathf.Clamp(vertVelocity, -50f, jumpForce);
            hasJumped = false;
            playerAnimator.SetBool("isJump", false);
        }
    }

    // UI , 플레이어 상태 관리
    void ControllPlayerState()
    {
        switch (playerState)
        {
            case PLAYERSTATE.gunIdle:
                GameManagerParameter.Instance().OnOffUI("CanvasPlayerUI", true);
                gameObject.GetComponent<Zoom>().enabled = true;
                gameObject.GetComponent<Binoculars>().enabled = true;
                mouseSensitivityX = mouseSensitivityIdleX;
                mouseSensitivityY = mouseSensitivityIdleY;
                playerAnimator.SetBool("isIdle(item)", false);
                playerAnimator.SetBool("isIdle(gun)", true);
                break;

            case PLAYERSTATE.useBinoculars:
                gameObject.GetComponent<Zoom>().enabled = false;
                GameManagerParameter.Instance().OnOffUI("CanvasBinoculars", true);
                break;
            case PLAYERSTATE.useZoom:
                gameObject.GetComponent<Binoculars>().enabled = false;
                break;
            case PLAYERSTATE.itemIdle:
                GameManagerParameter.Instance().OnOffUI("CanvasPlayerUI", true);
                gameObject.GetComponent<Zoom>().enabled = false;
                gameObject.GetComponent<Binoculars>().enabled = false;
                playerAnimator.SetBool("isIdle(item)", true);
                playerAnimator.SetBool("isIdle(gun)", false);
                break;
            case PLAYERSTATE.useCCTV:
                GameManagerParameter.Instance().OnOffUI("CanvasCCTV", true);
                break;
            case PLAYERSTATE.useMap:
                gameObject.GetComponent<Zoom>().enabled = false;
                gameObject.GetComponent<Binoculars>().enabled = false;
                break;
        }

    }
}
