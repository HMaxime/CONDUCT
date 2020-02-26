using UnityEngine;
using static Util;
//DONE
public class Mouvement : MonoBehaviour
{
    private Transform leftHand;
    private Transform rightHand;

    private Transform thumbLeft;
    private Transform indexLeft;
    private Transform middleLeft;
    private Transform pinkLeft;
    private Transform ringLeft;
    private Transform palmLeft;

    private Transform thumbRight;
    private Transform indexRight;
    private Transform middleRight;
    private Transform pinkRight;
    private Transform ringRight;
    private Transform palmRight;

    public Transform LeftHand { get => leftHand; }
    public Transform RightHand { get => rightHand; }
    public Transform ThumbLeft { get => thumbLeft; }
    public Transform IndexLeft { get => indexLeft; }
    public Transform MiddleLeft { get => middleLeft; }
    public Transform PinkLeft { get => pinkLeft; }
    public Transform RingLeft { get => ringLeft; }
    public Transform PalmLeft { get => palmLeft; }
    public Transform ThumbRight { get => thumbRight; }
    public Transform IndexRight { get => indexRight; }
    public Transform MiddleRight { get => middleRight; }
    public Transform PinkRight { get => pinkRight; }
    public Transform RingRight { get => ringRight; }
    public Transform PalmRight { get => palmRight; }

    private void Start()
    {
        leftHand = this.gameObject.transform.GetChild(1);
        rightHand = this.gameObject.transform.GetChild(0);

        thumbLeft = LeftHand.GetChild(0).GetChild(0);
        indexLeft = LeftHand.GetChild(1).GetChild(0);
        middleLeft = LeftHand.GetChild(2).GetChild(0);
        pinkLeft = LeftHand.GetChild(3).GetChild(0);
        ringLeft = LeftHand.GetChild(4).GetChild(0);
        palmLeft = LeftHand.GetChild(5);

        thumbRight = RightHand.GetChild(0).GetChild(0);
        indexRight = RightHand.GetChild(1).GetChild(0);
        middleRight = RightHand.GetChild(2).GetChild(0);
        pinkRight = RightHand.GetChild(3).GetChild(0);
        ringRight = RightHand.GetChild(4).GetChild(0);
        palmRight = RightHand.GetChild(5);
    }

    private void Update()
    {
        leftHand = this.gameObject.transform.GetChild(1);
        rightHand = this.gameObject.transform.GetChild(0);
    }


    public float[] getPositionsOfHands(int nbHand)
    {
        Transform hand;
        switch (nbHand)
        {
            case 0:
                hand = this.PalmLeft;
                break;
            case 1:
                hand = this.PalmRight;
                break;
            default:
                hand = this.PalmLeft;
                break;
        }
        return posTransformToArray(hand);
    }

    public float getDistanceBetween(Transform tr1, Transform tr2)
    {
        return ComputeDistance(posTransformToArray(tr1), posTransformToArray(tr2));
    }
}
